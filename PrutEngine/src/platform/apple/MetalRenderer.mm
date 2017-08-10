//
//  Renderer.m
//  adsf
//
//  Created by Heiko van der Heijden on 05/08/2017.
//  Copyright © 2017 Heiko van der Heijden. All rights reserved.
//

#import <simd/simd.h>
#import <ModelIO/ModelIO.h>
#import <MetalKit/MetalKit.h>
#import "prutengine/Application.hpp"
#import "prutengine/platform/apple/MetalRenderer.h"
#import "prutengine/platform/apple/AppDelegate.h"
#import <memory>
#import <cstdlib>

// Include header shared between C code here, which executes Metal API commands, and .metal files
#import "prutengine/platform/apple/MetalShaderTypes.h"


using namespace Prutengine;

Data::MetalShaderData::MetalShaderData(id<MTLFunction> mtlFunction) : ShaderData(PrutEngine::Graphics_Engine::AppleMetal){
    this->metalFunction = mtlFunction;
    //[library newFunctionWithName:[NSString stringWithUTF8String:path.c_str()]];
}


Data::MetalShaderData::MetalShaderData(Renderer* renderer, const std::string& name) : ShaderData(PrutEngine::Graphics_Engine::AppleMetal) {
    this->metalFunction = [[renderer getDefaultLibrary] newFunctionWithName:[NSString stringWithUTF8String:name.c_str()]];
}

id <MTLFunction> Data::MetalShaderData::getMetalFunction() const{
    return this->metalFunction;
}





Data::MetalPipeline::MetalPipeline(const std::string& name,const std::vector<std::shared_ptr<PrutEngine::Data::Shader>> &shaders,Renderer* renderer) : GraphicsProgram(name, shaders) {
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = [NSString stringWithUTF8String:name.c_str()];
    pipelineStateDescriptor.sampleCount = [renderer getRenderDestinationProvider].sampleCount;
    
    
    
    for(auto sh : shaders){
        MetalShaderData* tmp = static_cast<MetalShaderData*>(sh->getData().get());
        if(sh->getShaderType() == PrutEngine::Shader_Types::Fragment_Shader){
            pipelineStateDescriptor.fragmentFunction = tmp->getMetalFunction();//sh->getShaderData()->getMetalFunction();
        } else if (sh->getShaderType() == PrutEngine::Shader_Types::Vertex_Shader){
            pipelineStateDescriptor.vertexFunction = tmp->getMetalFunction();
        }
    }
    
    pipelineStateDescriptor.vertexDescriptor = [renderer getVertexDescriptor];
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = [renderer getRenderDestinationProvider].colorPixelFormat;
    
    //renderDestination.colorPixelFormat;
    pipelineStateDescriptor.depthAttachmentPixelFormat = [renderer getRenderDestinationProvider].depthStencilPixelFormat;
    
    //renderDestination.depthStencilPixelFormat;
    pipelineStateDescriptor.stencilAttachmentPixelFormat = [renderer getRenderDestinationProvider].depthStencilPixelFormat;
    //renderDestination.depthStencilPixelFormat;
    
    NSError *error = NULL;
    this->pipeline = [[renderer getDevice]newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    if (!this->pipeline){
        NSLog(@"Failed to created pipeline state, error %@", error);
        std::exit(-1);
    }
    
}


id <MTLRenderPipelineState> Data::MetalPipeline::getPipeline() const{
    return this->pipeline;
}

// The max number of command buffers in flight
static const NSUInteger kMaxBuffersInFlight = 3;

// The 256 byte aligned size of our uniform structure
static const size_t kAlignedUniformsSize = (sizeof(Uniforms) & ~0xFF) + 0x100;

// Main class performing the rendering
@implementation Renderer
{
    std::unique_ptr<PrutEngine::Platform::MacFriend> macFriend;
    dispatch_semaphore_t _inFlightSemaphore;
    id <MTLDevice> _device;
    id <MTLCommandQueue> _commandQueue;
    id <MTLLibrary> _defaultLibrary;
    
    // Metal objects
    id <MTLBuffer> _dynamicUniformBuffer;
    //id <MTLRenderPipelineState> _pipelineState;
    id <MTLDepthStencilState> _depthState;
    id <MTLTexture> _colorMap;
    std::shared_ptr<Data::MetalPipeline> pipe;
    // Metal vertex descriptor specifying how vertices will by laid out for input into our render
    //   pipeline and how we'll layout our Model IO verticies
    MTLVertexDescriptor *_mtlVertexDescriptor;
    
    // The object controlling the ultimate render destination
    __strong id<RenderDestinationProvider> _renderDestination;
    
    // Offset within _dynamicUniformBuffer to set for the current frame
    uint32_t _uniformBufferOffset;
    
    // Used to determine _uniformBufferStride each frame.
    //   This is the current frame number modulo kMaxBuffersInFlight
    uint8_t _uniformBufferIndex;
    
    // Address to write dynamic uniforms to each frame
    void* _uniformBufferAddress;
    
    // Projection matrix calculated as a function of view size
    matrix_float4x4 _projectionMatrix;
    
    // Current rotation of our object in radians
    float _rotation;
    
    // MetalKit mesh containing vertex data and index buffer for our object
    MTKMesh *_mesh;
}


-(nonnull instancetype) initWithMetalDevice:(nonnull id<MTLDevice>)device
                  renderDestinationProvider:(nonnull id<RenderDestinationProvider>)renderDestinationProvider
{
    self = [super init];
    if(self)
    {
    
        macFriend = std::unique_ptr<PrutEngine::Platform::MacFriend>(new PrutEngine::Platform::MacFriend());
  
        
        //macFriend->setLoadShader(
         //                      );
        
        //   macFriend->disableLoadShader();
        _device = device;
        _renderDestination = renderDestinationProvider;
        _inFlightSemaphore = dispatch_semaphore_create(kMaxBuffersInFlight);
        

        [self _loadMetal];
        [self _loadAssets];
    
         macFriend->awake();
        
    }
    
    return self;
}

-(MTLVertexDescriptor *) getVertexDescriptor{
    return _mtlVertexDescriptor;
}

-(id <MTLLibrary>) getDefaultLibrary{
    return _defaultLibrary;
}

-(id<MTLDevice>) getDevice{
    return _device;
}

-(id<RenderDestinationProvider>) getRenderDestinationProvider{
    return _renderDestination;
}
//(compileProgram

- (void)_loadMetal
{
    using namespace PrutEngine::Data;
    using namespace PrutEngine;
   
  
    _defaultLibrary = [_device newDefaultLibrary];
    
    
   
    const auto ldshader = std::function<void(std::string, PrutEngine::Shader_Types, PrutEngine::Data::Shader*)>([self](std::string path, PrutEngine::Shader_Types type, PrutEngine::Data::Shader* shader)->void{
        shader->setShader(new Prutengine::Data::MetalShaderData(self, path));
    });
    
    macFriend->setLoadShader(ldshader);

    const auto compileProgram = std::function<PrutEngine::Data::GraphicsProgram*(const std::string& name, const std::vector<std::shared_ptr<PrutEngine::Data::Shader>>& shaders)>([self](const std::string& name, const std::vector<std::shared_ptr<PrutEngine::Data::Shader>>& shaders) -> PrutEngine::Data::GraphicsProgram* {
        return new Prutengine::Data::MetalPipeline(name,shaders,self);
        
    });
    
    macFriend->setCompileProgram(compileProgram);
    
    NSUInteger uniformBufferSize = kAlignedUniformsSize * kMaxBuffersInFlight;
    
    // Create and allocate our uniform buffer object.  Indicate shared storage so that both the
    //  CPU can access the buffer
    _dynamicUniformBuffer = [_device newBufferWithLength:uniformBufferSize
                                                 options:MTLResourceStorageModeShared];
    
    _dynamicUniformBuffer.label = @"UniformBuffer";

    
  //  id <MTLFunction> fragmentFunction = [_defaultLibrary newFunctionWithName:@"fragmentLighting"];
 
    
    //auto fragment = std::shared_ptr<PrutEngine::Data::ShaderData>(new Data::MetalShaderData(fragmentFunction));
    auto fragment = std::shared_ptr<Shader>(new Shader("fragmentLighting",PrutEngine::Shader_Types::Fragment_Shader));
    ///fragment->setShader(new Prutengine::Data::MetalShaderData(fragmentFunction));
    
    // Load the vertex function into the library
   //id <MTLFunction> vertexFunction = [_defaultLibrary newFunctionWithName:@"vertexTransform"];
    //auto vertex = std::shared_ptr<PrutEngine::Data::ShaderData>(new Data::MetalShaderData(vertexFunction));
    auto vertex = std::shared_ptr<Shader>(new Shader("vertexTransform",PrutEngine::Shader_Types::Vertex_Shader));
   // vertex->setShader(new Prutengine::Data::MetalShaderData(vertexFunction));
    
    std::vector<std::shared_ptr<PrutEngine::Data::Shader>> dat;
    dat.push_back(fragment);
    dat.push_back(vertex);
    
    
    _renderDestination.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    _renderDestination.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    _renderDestination.sampleCount = 1;
    
    
    
    // Create a vertex descriptor for our Metal pipeline. Specifies the layout of vertices the
    //   pipeline should expect.  The layout below keeps attributes used to calculate vertex shader
    //   output position separate (world position, skinning, tweening weights) separate from other
    //   attributes (texture coordinates, normals).  This generally maximizes pipeline efficiency
    
    _mtlVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    
    // Positions.
    _mtlVertexDescriptor.attributes[kVertexAttributePosition].format = MTLVertexFormatFloat3;
    _mtlVertexDescriptor.attributes[kVertexAttributePosition].offset = 0;
    _mtlVertexDescriptor.attributes[kVertexAttributePosition].bufferIndex = kBufferIndexMeshPositions;
    
    // Texture coordinates.
    _mtlVertexDescriptor.attributes[kVertexAttributeTexcoord].format = MTLVertexFormatFloat2;
    _mtlVertexDescriptor.attributes[kVertexAttributeTexcoord].offset = 0;
    _mtlVertexDescriptor.attributes[kVertexAttributeTexcoord].bufferIndex = kBufferIndexMeshGenerics;
    
    // Normals.
    _mtlVertexDescriptor.attributes[kVertexAttributeNormal].format = MTLVertexFormatHalf4;
    _mtlVertexDescriptor.attributes[kVertexAttributeNormal].offset = 8;
    _mtlVertexDescriptor.attributes[kVertexAttributeNormal].bufferIndex = kBufferIndexMeshGenerics;
    
    // Position Buffer Layout
    _mtlVertexDescriptor.layouts[kBufferIndexMeshPositions].stride = 12;
    _mtlVertexDescriptor.layouts[kBufferIndexMeshPositions].stepRate = 1;
    _mtlVertexDescriptor.layouts[kBufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;
    
    // Generic Attribute Buffer Layout
    _mtlVertexDescriptor.layouts[kBufferIndexMeshGenerics].stride = 16;
    _mtlVertexDescriptor.layouts[kBufferIndexMeshGenerics].stepRate = 1;
    _mtlVertexDescriptor.layouts[kBufferIndexMeshGenerics].stepFunction = MTLVertexStepFunctionPerVertex;

    
    pipe = std::shared_ptr<Prutengine::Data::MetalPipeline>(new Prutengine::Data::MetalPipeline("MyPdsipeline", dat, self));

    MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStateDesc.depthCompareFunction = MTLCompareFunctionLess;
    depthStateDesc.depthWriteEnabled = YES;
    _depthState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];
    
    // Create the command queue
    _commandQueue = [_device newCommandQueue];
}

- (void)_loadAssets
{
    // Create and load our assets into Metal objects including meshes and textures
    
    NSError *error;
    
    // Create a MetalKit mesh buffer allocator so that ModelIO will load mesh data directly into
    //   Metal buffers accessible by the GPU
    MTKMeshBufferAllocator *metalAllocator = [[MTKMeshBufferAllocator alloc]
                                              initWithDevice: _device];
    
    // Use Model IO to create a box mesh as our object
    MDLMesh *mdlMesh = [MDLMesh newBoxWithDimensions:(vector_float3){4, 4, 4}
                                            segments:(vector_uint3){2, 2, 2}
                                        geometryType:MDLGeometryTypeTriangles
                                       inwardNormals:NO
                                           allocator:metalAllocator];
    
    // Creata a Model IO vertexDescriptor so that we format/layout our model IO mesh vertices to
    //   fit our Metal render pipeline's vertex descriptor layout
    MDLVertexDescriptor *mdlVertexDescriptor =
    MTKModelIOVertexDescriptorFromMetal(_mtlVertexDescriptor);
    
    // Indicate how each Metal vertex descriptor attribute maps to each ModelIO attribute
    mdlVertexDescriptor.attributes[kVertexAttributePosition].name  = MDLVertexAttributePosition;
    mdlVertexDescriptor.attributes[kVertexAttributeTexcoord].name  = MDLVertexAttributeTextureCoordinate;
    mdlVertexDescriptor.attributes[kVertexAttributeNormal].name    = MDLVertexAttributeNormal;
    
    // Perform the format/relayout of mesh vertices by setting the new vertex descriptor in our
    //   Model IO mesh
    mdlMesh.vertexDescriptor = mdlVertexDescriptor;
    
    // Crewte a MetalKit mesh (and submeshes) backed by Metal buffers
    _mesh = [[MTKMesh alloc] initWithMesh:mdlMesh
                                   device:_device
                                    error:&error];
    
    if(!_mesh || error)
    {
        NSLog(@"Error creating MetalKit mesh %@", error.localizedDescription);
    }
    
    // Use MetalKit's to load textures from our asset catalog (Assets.xcassets)
    MTKTextureLoader* textureLoader = [[MTKTextureLoader alloc] initWithDevice:_device];
    
    // Load our textures with shader read using private storage
    NSDictionary *textureLoaderOptions =
    @{
      MTKTextureLoaderOptionTextureUsage       : @(MTLTextureUsageShaderRead),
      MTKTextureLoaderOptionTextureStorageMode : @(MTLStorageModePrivate)
      };
    
   // NSImage *controlImage = [[NSImage alloc] initWithContentsOfFile:@""];
    //NSBitmapImageRep *imageRep = [[controlImage representations] objectAtIndex:0];
    
    
    
    NSURL *baseURL = [NSURL fileURLWithPath:@"/Users/heikovanderheijden/Desktop/PrutEngine/build/examples/BasicApplication/Debug/Assets/Textures/cube.bmp"];
    _colorMap = [textureLoader newTextureWithContentsOfURL:baseURL options:textureLoaderOptions error:&error];
    
    if(!_colorMap || error)
    {
        NSLog(@"Error creating texture %@", error.localizedDescription);
    }
}

- (void)_updateDynamicBufferState
{
    // Update the location(s) to which we'll write to in our dynamically changing Metal buffers for
    //   the current frame (i.e. update our slot in the ring buffer used for the current frame)
    
    _uniformBufferIndex = (_uniformBufferIndex + 1) % kMaxBuffersInFlight;
    
    _uniformBufferOffset = kAlignedUniformsSize * _uniformBufferIndex;
    
    _uniformBufferAddress = ((uint8_t*)_dynamicUniformBuffer.contents) + _uniformBufferOffset;
}

- (void)_updateGameState
{
    macFriend->loop();
    // Update any game state (including updating dynamically changing Metal buffer)
    
    Uniforms * uniforms = (Uniforms*)_uniformBufferAddress;
    
    vector_float3 ambientLightColor = {0.02, 0.02, 0.02};
    uniforms->ambientLightColor = ambientLightColor;
    
    vector_float3 directionalLightDirection = {0, 0, -1.0};
    directionalLightDirection = vector_normalize(directionalLightDirection);
    uniforms->directionalLightDirection = directionalLightDirection;
    
    vector_float3 directionalLightColor = {.7, .7, .7};
    uniforms->directionalLightColor = directionalLightColor;;
    
    uniforms->materialShininess = 30;
    
    uniforms->viewMatrix = matrix4x4_translation(0.0, 0.0, -8.0);
    uniforms->projectionMatrix = _projectionMatrix;
    
    vector_float3 rotationAxis = {1, 1, 0};
    matrix_float4x4 modelMatrix = matrix4x4_rotation(_rotation, rotationAxis);
    
    uniforms->modelViewMatrix = matrix_multiply(uniforms->viewMatrix, modelMatrix);
    
    uniforms->normalMatrix = matrix3x3_upper_left(uniforms->modelViewMatrix);
    uniforms->normalMatrix = matrix_invert(matrix_transpose(uniforms->normalMatrix));
    
    _rotation += .01;
}

- (void)drawRectResized:(CGSize)size
{
    // When reshape is called, update the aspect ratio and projection matrix since the view
    //   orientation or size has changed
    float aspect = size.width / (float)size.height;
    _projectionMatrix = matrix_perspective_right_hand(65.0f * (M_PI / 180.0f), aspect, 0.1f, 100.0f);
}

- (void)update
{
    // Wait to ensure only kMaxBuffersInFlight are getting proccessed by any stage in the Metal
    //   pipeline (App, Metal, Drivers, GPU, etc)
    dispatch_semaphore_wait(_inFlightSemaphore, DISPATCH_TIME_FOREVER);
    
    // Create a new command buffer for each renderpass to the current drawable
    id <MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    commandBuffer.label = @"MyCommand";
    
    // Add completion hander which signal _inFlightSemaphore when Metal and the GPU has fully
    //   finished proccssing the commands we're encoding this frame.  This indicates when the
    //   dynamic buffers, that we're writing to this frame, will no longer be needed by Metal
    //   and the GPU.
    __block dispatch_semaphore_t block_sema = _inFlightSemaphore;
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer)
     {
         dispatch_semaphore_signal(block_sema);
     }];
    
    [self _updateDynamicBufferState];
    
    [self _updateGameState];
    
    // Obtain a renderPassDescriptor generated from the view's drawable textures
    MTLRenderPassDescriptor* renderPassDescriptor = _renderDestination.currentRenderPassDescriptor;
    
    // If we've gotten a renderPassDescriptor we can render to the drawable, otherwise we'll skip
    //   any rendering this frame because we have no drawable to draw to
    if(renderPassDescriptor != nil) {
        
        // Create a render command encoder so we can render into something
        id <MTLRenderCommandEncoder> renderEncoder =
        [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        renderEncoder.label = @"MyRenderEncoder";
        
        // Push a debug group allowing us to identify render commands in the GPU Frame Capture tool
        [renderEncoder pushDebugGroup:@"DrawBox"];
        
        // Set render command encoder state
        [renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
        [renderEncoder setCullMode:MTLCullModeBack];
        
        [renderEncoder setRenderPipelineState:pipe->getPipeline()];
        [renderEncoder setDepthStencilState:_depthState];
        
        // Set any buffers fed into our render pipeline
        [renderEncoder setVertexBuffer:_dynamicUniformBuffer
                                offset:_uniformBufferOffset
                               atIndex:kBufferIndexUniforms];
        
        [renderEncoder setFragmentBuffer:_dynamicUniformBuffer
                                  offset:_uniformBufferOffset
                                 atIndex:kBufferIndexUniforms];
        
        // Set mesh's vertex buffers
        for (NSUInteger bufferIndex = 0; bufferIndex < _mesh.vertexBuffers.count; bufferIndex++)
        {
            MTKMeshBuffer *vertexBuffer = _mesh.vertexBuffers[bufferIndex];
            if((NSNull*)vertexBuffer != [NSNull null])
            {
                [renderEncoder setVertexBuffer:vertexBuffer.buffer
                                        offset:vertexBuffer.offset
                                       atIndex:bufferIndex];
            }
        }
        
        // Set any textures read/sampled from our render pipeline
        [renderEncoder setFragmentTexture:_colorMap
                                  atIndex:kTextureIndexColor];
        
        // Draw each submesh of our mesh
        for(MTKSubmesh *submesh in _mesh.submeshes)
        {
            [renderEncoder drawIndexedPrimitives:submesh.primitiveType
                                      indexCount:submesh.indexCount
                                       indexType:submesh.indexType
                                     indexBuffer:submesh.indexBuffer.buffer
                               indexBufferOffset:submesh.indexBuffer.offset];
        }
        
        [renderEncoder popDebugGroup];
        
        // We're done encoding commands
        [renderEncoder endEncoding];
    }
    
    // Schedule a present once the framebuffer is complete using the current drawable
    [commandBuffer presentDrawable:_renderDestination.currentDrawable];
    
    // Finalize rendering here & push the command buffer to the GPU
    [commandBuffer commit];
}

// Generic matrix math utiliy functions
#pragma mark Matrix Math Utilites

matrix_float4x4 __attribute__((__overloadable__))
matrix_make(float m00, float m10, float m20, float m30,
            float m01, float m11, float m21, float m31,
            float m02, float m12, float m22, float m32,
            float m03, float m13, float m23, float m33)
{
    return (matrix_float4x4){ {
        { m00, m10, m20, m30 },
        { m01, m11, m21, m31 },
        { m02, m12, m22, m32 },
        { m03, m13, m23, m33 } } };
}

matrix_float3x3 __attribute__((__overloadable__))
matrix_make(vector_float3 col0, vector_float3 col1, vector_float3 col2)
{
    return (matrix_float3x3){ {col0, col1, col2} };
}

matrix_float3x3 matrix3x3_upper_left(matrix_float4x4 m)
{
    vector_float3 x = m.columns[0].xyz;
    vector_float3 y = m.columns[1].xyz;
    vector_float3 z = m.columns[2].xyz;
    return matrix_make(x, y, z);
}

matrix_float4x4 matrix4x4_translation(float tx, float ty, float tz)
{
    return matrix_make(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       tx, ty, tz, 1);
}

matrix_float4x4 matrix4x4_rotation(float radians, vector_float3 axis)
{
    axis = vector_normalize(axis);
    float ct = cosf(radians);
    float st = sinf(radians);
    float ci = 1 - ct;
    float x = axis.x, y = axis.y, z = axis.z;
    return matrix_make(ct + x * x * ci, y * x * ci + z * st, z * x * ci - y * st, 0,
                       x * y * ci - z * st, ct + y * y * ci, z * y * ci + x * st, 0,
                       x * z * ci + y * st, y * z * ci - x * st, ct + z * z * ci, 0,
                       0, 0, 0, 1);
}

matrix_float4x4 matrix_perspective_right_hand(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float ys = 1 / tanf(fovyRadians * 0.5);
    float xs = ys / aspect;
    float zs = farZ / (nearZ - farZ);
    return matrix_make(xs, 0, 0,  0,
                       0, ys, 0,  0,
                       0, 0, zs, -1,
                       0, 0, nearZ * zs, 0);
}

@end





