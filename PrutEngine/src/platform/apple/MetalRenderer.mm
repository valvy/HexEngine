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

#import "prutengine/platform/MetalRenderer.h"

// Include header shared between C code here, which executes Metal API commands, and .metal files
#import "prutengine/platform/MetalShaderTypes.h"

// The max number of command buffers in flight
static const NSUInteger kMaxBuffersInFlight = 3;

// The 256 byte aligned size of our uniform structure
static const size_t kAlignedUniformsSize = (sizeof(Uniforms) & ~0xFF) + 0x100;

// Main class performing the rendering
@implementation Renderer
{
    dispatch_semaphore_t _inFlightSemaphore;
    id <MTLDevice> _device;
    id <MTLCommandQueue> _commandQueue;
    id <MTLLibrary> _defaultLibrary;

    // Metal objects
    id <MTLBuffer> _dynamicUniformBuffer;
    id <MTLRenderPipelineState> _pipelineState;
    id <MTLDepthStencilState> _depthState;
    id <MTLTexture> _colorMap;

    // Metal vertex descriptor specifying how vertices will by laid out for input into our render
    //   pipeline and how we'll layout our Model IO verticies
    MTLVertexDescriptor *_mtlVertexDescriptor;

    // The object controlling the ultimate render destination
    __weak id<RenderDestinationProvider> _renderDestination;

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
        _device = device;
        _renderDestination = renderDestinationProvider;
        _inFlightSemaphore = dispatch_semaphore_create(kMaxBuffersInFlight);
        [self _loadMetal];
       // [self _loadAssets];
    }

    return self;
}

- (void)_loadMetal
{


    // Load all the shader files with a metal file extension in the project
    _defaultLibrary = [_device newDefaultLibrary];

    NSUInteger uniformBufferSize = kAlignedUniformsSize * kMaxBuffersInFlight;

    // Create and allocate our uniform buffer object.  Indicate shared storage so that both the
    //  CPU can access the buffer
    _dynamicUniformBuffer = [_device newBufferWithLength:uniformBufferSize
                                                 options:MTLResourceStorageModeShared];

    _dynamicUniformBuffer.label = @"UniformBuffer";

    // Load the fragment function into the library
    id <MTLFunction> fragmentFunction = [_defaultLibrary newFunctionWithName:@"fragmentLighting"];

    // Load the vertex function into the library
    id <MTLFunction> vertexFunction = [_defaultLibrary newFunctionWithName:@"vertexTransform"];

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

    _renderDestination.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    _renderDestination.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    _renderDestination.sampleCount = 1;
    
    // Create a reusable pipeline state
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = @"MyPipeline";
    pipelineStateDescriptor.sampleCount = _renderDestination.sampleCount;
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.vertexDescriptor = _mtlVertexDescriptor;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = _renderDestination.colorPixelFormat;
    pipelineStateDescriptor.depthAttachmentPixelFormat = _renderDestination.depthStencilPixelFormat;
    pipelineStateDescriptor.stencilAttachmentPixelFormat = _renderDestination.depthStencilPixelFormat;

    NSError *error = NULL;
    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    if (!_pipelineState)
    {
        NSLog(@"Failed to created pipeline state, error %@", error);
    }

    MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStateDesc.depthCompareFunction = MTLCompareFunctionLess;
    depthStateDesc.depthWriteEnabled = YES;
    _depthState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];

    // Create the command queue
    _commandQueue = [_device newCommandQueue];
}


- (void)_updateDynamicBufferState
{
    // Update the location(s) to which we'll write to in our dynamically changing Metal buffers for
    //   the current frame (i.e. update our slot in the ring buffer used for the current frame)

    _uniformBufferIndex = (_uniformBufferIndex + 1) % kMaxBuffersInFlight;

    _uniformBufferOffset = kAlignedUniformsSize * _uniformBufferIndex;

    _uniformBufferAddress = ((uint8_t*)_dynamicUniformBuffer.contents) + _uniformBufferOffset;
}


- (void)drawRectResized:(CGSize)size{

}

- (void)update
{
    // Wait to ensure only kMaxBuffersInFlight are getting proccessed by any stage in the Metal
    //   pipeline (App, Metal, Drivers, GPU, etc)
    dispatch_semaphore_wait(_inFlightSemaphore, DISPATCH_TIME_FOREVER);

    // Create a new command buffer for each renderpass to the current drawable
    id <MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    commandBuffer.label = @"MyCommand";


    __block dispatch_semaphore_t block_sema = _inFlightSemaphore;
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer)
    {
        dispatch_semaphore_signal(block_sema);
    }];

    [self _updateDynamicBufferState];


    // Obtain a renderPassDescriptor generated from the view's drawable textures
    MTLRenderPassDescriptor* renderPassDescriptor = _renderDestination.currentRenderPassDescriptor;

    // If we've gotten a renderPassDescriptor we can render to the drawable, otherwise we'll skip
    //   any rendering this frame because we have no drawable to draw to
    if(renderPassDescriptor != nil) {

        // Create a render command encoder so we can render into something
        id <MTLRenderCommandEncoder> renderEncoder =
        [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];

        
        [renderEncoder popDebugGroup];
        
        // We're done encoding commands
        [renderEncoder endEncoding];
    }

    // Schedule a present once the framebuffer is complete using the current drawable
    [commandBuffer presentDrawable:_renderDestination.currentDrawable];

    // Finalize rendering here & push the command buffer to the GPU
    [commandBuffer commit];
}

@end



