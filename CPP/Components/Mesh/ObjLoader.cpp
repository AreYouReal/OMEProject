#include "ObjLoader.hpp"


#ifdef __APPLE__
#define VERTEX_SHADER "wiredObj.vert"
#define FRAGMENT_SHADER "wiredObj.frag"
#else
#define VERTEX_SHADER "shaders/wiredObj.vert"
#define FRAGMENT_SHADER "shaders/wiredObj.frag"
#endif


#include "GameObject.hpp"
#include "Camera.hpp"

namespace OME {
    
    string meshesNames[] = {"Cone.obj", "Sphere.obj", "Torus.obj", "Monkey.obj", "IsoSphere.obj"};
    
    
    int stride;
    GLvoid* offset;
    GLvoid* offsetTexCoord;
    
    ObjLoader::ObjLoader(){
    }
    
    ObjLoader::~ObjLoader(){
    }
    
    
    bool ObjLoader::init(){
        program.loadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
        
        loadMesh();
        
        return true;
    }
    
    void ObjLoader::draw(){
        program.use();
    
        glm::mat4 modelMatrix   = go->transform()->getMatrix();
        glm::mat4 viewMat       = Camera::instance()->getViewMatrix();
        glm::mat4 projMatrix    = Camera::instance()->getProjectionMatrix();
        
        program.setUniform("model",      modelMatrix);
        program.setUniform("view",       viewMat);
        program.setUniform("projection", projMatrix);
        
        
        glBindVertexArray(vao);
        
        glDrawArrays(GL_LINES, 0, indexCount);
        
        glBindVertexArray(0);
        
        
    }
    
    void ObjLoader::switchModel(){
        ++modelNum;
        modelNum = modelNum % 5;
        loadMesh();
    }
    
    
    void ObjLoader::loadMesh(){
        string fileName = "";
#ifdef __APPLE__
        fileName = Utils::extractPath(getenv("FILESYSTEM"));
#else
        fileName = "/storage/emulated/0/Android/data/com.areyoureal.ome/files/";
#endif
        
        fileName = fileName + meshesNames[modelNum];
        
        objMeshModel = wfObj.parseObjModel(fileName);
        indexCount = wfObj.indexTotal();
        stride = (2 * sizeof(vec3) + sizeof(vec2) + sizeof(vec4) );
        offset = (GLvoid*)(sizeof(vec3) + sizeof(vec2));
        offsetTexCoord = (GLvoid*)(sizeof(vec3));
        
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, objMeshModel->vertices.size() * sizeof(objMeshModel->vertices[0]), &objMeshModel->vertices[0], GL_STATIC_DRAW);
        
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(ShaderProgram::VERTEX_ATTRIB_LOCATION);
        glEnableVertexAttribArray(ShaderProgram::NORMAL_ATTRIB_LOCATION);
        glEnableVertexAttribArray(ShaderProgram::TEXCOORD_ATTRIB_LOCATION);
        glVertexAttribPointer(ShaderProgram::VERTEX_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, stride, 0);
        glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, stride, offsetTexCoord);
        glVertexAttribPointer(ShaderProgram::TEXCOORD_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, stride, offset);
        glBindVertexArray(0);
        
        objMeshModel->vertices.clear();
    }
    
    
    
    
    
}
