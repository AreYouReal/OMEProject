#include "ObjLoader.hpp"

#include "Time.hpp"

#ifdef __APPLE__
#define G_VERTEX_SHADER "gouraud.vert"
#define G_FRAGMENT_SHADER "gouraud.frag"
#define P_VERTEX_SHADER "phong.vert"
#define P_FRAGMENT_SHADER "phong.frag"
#else
#define G_VERTEX_SHADER "shaders/gouraud.vert"
#define G_FRAGMENT_SHADER "shaders/gouraud.frag"
#define P_VERTEX_SHADER "shaders/phong.vert"
#define P_FRAGMENT_SHADER "shaders/phong.frag"
#endif


#include "GameObject.hpp"
#include "Camera.hpp"

namespace OME {
    
    string meshesNames[] = {"SemiHollowCylinder.obj", "Sphere.obj", "Torus.obj", "Monkey.obj", "IsoSphere.obj", "Cone.obj"};
    
    
    int stride;
    GLvoid* offset;
    GLvoid* offsetTexCoord;
    
    ObjLoader::ObjLoader(){
    }
    
    ObjLoader::~ObjLoader(){
    }
    
    
    bool ObjLoader::init(){
        gouraud.loadShaders(G_VERTEX_SHADER, G_FRAGMENT_SHADER);
        phong.loadShaders(P_VERTEX_SHADER, P_FRAGMENT_SHADER);
        program = phong;
        
        loadMesh();
        
        return true;
    }
    
    void ObjLoader::draw(){
        static float rot = 0.0f;
        rot += 1.0f * Time::deltaTime();
        if(rot > 360.0f){
            rot = 0.0f;
        }
        
        
        go->transform()->mRotation = vec3(0.0f, rot, 0.0f);
        
        Camera::instance()->pushMatrix(go->transform()->getMatrix());
        

        
        
        program.use();
    
        glm::mat4 modelMatrix   = go->transform()->getMatrix();
        glm::mat4 viewMat       = Camera::instance()->getViewMatrix();
        glm::mat4 projMatrix    = Camera::instance()->getProjectionMatrix();
        glm::mat3 normalMatrix  = Camera::instance()->getNormalMatrix();
        
        program.setUniform("transform.model",      modelMatrix);
        program.setUniform("transform.view",       viewMat);
        program.setUniform("transform.projection", projMatrix);
        program.setUniform("transform.normal",     normalMatrix);
        
        glm::vec3 matAmbient(0.3f, 0.3f, 0.3f);
        glm::vec3 matDiffuse(0.5f, 0.5f, 0.5f);
        glm::vec3 matSpecular(1.0f, 0.0f, 0.0f);
        float shininess = 40;
        
        program.setUniform("material.ambient", matAmbient);
        program.setUniform("material.diffuse", matDiffuse);
        program.setUniform("material.specular", matSpecular);
        program.setUniform("material.shininess", shininess);

        
        glm::vec4 lightPos(10.0f, 10.0f, 10.0f, 1.0f);
        
        glm::vec3 lightInViewPos = viewMat * lightPos;
        
        glm::vec3 lightAmbient(1.0f, 1.0f, 1.0f);
        glm::vec3 lightDiffuse(1.0f, 1.0f, 1.0f);
        glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);
        
        program.setUniform("light.position", lightInViewPos);
        program.setUniform("light.ambient", lightAmbient);
        program.setUniform("light.diffuse", lightDiffuse);
        program.setUniform("light.specular", lightSpecular);
        
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0, indexCount);
        
        glBindVertexArray(0);
        
        Camera::instance()->popMatrix();
    }
    
    void ObjLoader::switchModel(){

//        static bool perVertex = false;
//        perVertex = !perVertex;
//        if(perVertex){
//            program = gouraud;
//        }else{
//            program = phong;
//        }
        
        
        ++modelNum;
        modelNum = modelNum % 6;
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
        stride = (2 * sizeof(vec3) ) + sizeof(vec2) + sizeof(vec4);
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
        glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, stride, offset);
        glVertexAttribPointer(ShaderProgram::TEXCOORD_ATTRIB_LOCATION, 2, GL_FLOAT, GL_FALSE, stride, offsetTexCoord);
        glBindVertexArray(0);
        
        objMeshModel->vertices.clear();
    }
}
