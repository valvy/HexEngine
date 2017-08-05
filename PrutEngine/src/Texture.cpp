#include "prutengine/data/Texture.hpp"
#include <fstream>
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include "prutengine/Application.hpp"
using namespace PrutEngine;
using namespace PrutEngine::Data;

Texture::Texture(std::string name) : AbstractResource(name){
    const Graphics_Engine engine = Application::getInstance()->getCurrentGraphicsEngine();
    if(engine == Graphics_Engine::AppleMetal){
        return;
    }
    std::fstream str(name, std::ios::in | std::ios::binary | std::ios::ate);
    if(str.good()){
          //Read the header.. (this contains things like image width/height.. or the kind of file (such if it's a bmp)
          unsigned char header[54];
          
          str.seekp(0);
          str.read((char*)header,sizeof(unsigned char) * 54); //read the header of the bitmap
          
          
          //Check if it's an bmp... otherwise it just won't work
          if(header[0] != 'B' || header[1] != 'M'){
              str.close();
              return;
          }
         
          unsigned int dataPos = *(int*)&(header[0x0A]); //the position where the pixels starts
          unsigned int imageSize = *(int*)&(header[0x22]);//The amount of pixels.
          
          //Get size of the image
          unsigned int width = *(int*)&(header[0x12]);
          unsigned int height = *(int*)&(header[0x16]);
          
          //Get the actual pixels
          unsigned char pixels[imageSize];
          
          str.seekp(dataPos);
          str.read((char*)pixels,sizeof(unsigned char) * imageSize);
          str.close(); //the file is no longer needed
          
          //Give it to opengl :-)
          glGenTextures(1, &this->texture);
          glBindTexture(GL_TEXTURE_2D,this->texture);
          
          
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          
         
          glTexImage2D(GL_TEXTURE_2D, // target
                       0,  // level, 0 = base, no minimap,
                       GL_RGBA, // internalformat
                       width,  // width
                       height,  // height
                       0,  // border, always 0 in OpenGL ES
                       GL_BGR,  // format
                       GL_UNSIGNED_BYTE, // type
                       pixels);
          
          
      }else{
          str.close();
          throw Exceptions::AssetNotLoadedException(std::string("Could not find :") + name);
      }
}


GLuint Texture::getTexture() const{
    return this->texture;
}

Texture::~Texture(){
    const Graphics_Engine engine = Application::getInstance()->getCurrentGraphicsEngine();
    
    if(engine == Graphics_Engine::AppleMetal){
        return;
    }
    glDeleteTextures(1, &this->texture);
}
