#include "ObjLoader.hpp"

#include "Time.hpp"

#ifdef __APPLE__
#define G_VERTEX_SHADER "gouraud.vert"
#define G_FRAGMENT_SHADER "gouraud.frag"
#define P_VERTEX_SHADER "polkaDot.vert"
#define P_FRAGMENT_SHADER "polkaDot.frag"
#else
#define G_VERTEX_SHADER "shaders/one_light/gouraud.vert"
#define G_FRAGMENT_SHADER "shaders/one_light/gouraud.frag"
#define P_VERTEX_SHADER "shaders/one_light/ripple.vert"
#define P_FRAGMENT_SHADER "shaders/one_light/ripple.frag"
#endif

#include "GameObject.hpp"
#include "Camera.hpp"

#include "Illuminator.hpp"

namespace OME {
    
    string meshesNames[] = {"SubDividedPlane.obj", "SemiHollowCylinder.obj", "Sphere.obj", "Torus.obj", "Monkey.obj", "IsoSphere.obj", "Cone.obj"};
    
    float direction = 0.0f;
    
    int stride;
    GLvoid* offset;
    GLvoid* offsetTexCoord;
    
    GLint drawType = GL_TRIANGLES;
    
    float time;
    
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
        rot += .1f * Time::deltaTime();
        if(rot > 10.0f){
            rot = 0.0f;
        }
//
//        go->transform()->mRotation = vec3(rot/2, 0.0f, rot);
        
        
        
        Light *l = Illuminator::instance()->getLight();
        
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
        
        glm::vec3 matAmbient(0.1f, 0.1f, 0.1f);
        glm::vec3 matDiffuse(0.7f, 0.1f, 0.5f);
        glm::vec3 matSpecular(1.0f, 1.0f, 1.0f);
        float shininess = 40;
        
        program.setUniform("material.ambient", matAmbient);
        program.setUniform("material.diffuse", matDiffuse);
        program.setUniform("material.specular", matSpecular);
        program.setUniform("material.shininess", shininess);
        
        program.setUniform("directionLight", direction);

        // CIRCULAR ROTATION
//        glm::vec3 mColor(0.50, 0.50, 1.0);
//        program.setUniform("modelColor", mColor);
//        glm::vec3 dColor(1.0, 1.0, 1.0);
//        program.setUniform("dotColor", dColor);
//        program.setUniform("side", 50);
//
//        program.setUniform("radianAngle", rot);
        //_______________________


        // BRICK SHADER
//        glm::vec3 brickColor(1.0f, 0.3f, 0.2f);
//        glm::vec3 mortarColor(0.85f, 0.86f, 0.84f);
//        glm::vec2 rectSize(0.4f, 0.1f);
//        glm::vec2 brickPercent(0.90f, 0.85f);
//        
//        program.setUniform("brickColor", brickColor);
//        program.setUniform("mortarColor", mortarColor);
//        program.setUniform("rectangularSize", rectSize);
//        program.setUniform("brickPercent", brickPercent);
        //______________________
        
        
        program.setUniform("side", 0.30);
        program.setUniform("dotSize", 0.13);
        
        glm::vec3 modelColor(1.0, 1.0, 1.0);
        glm::vec3 dotColor(0.0f, 0.0f, .7f);
        glm::vec3 backSideModelColor(0.0f, 0.7f, 0.0f);
        glm::vec3 backSideDotColor(0.8f, 0.2f, 0.0f);
        
        program.setUniform("modelColor", modelColor);
        program.setUniform("dotColor", dotColor);
        program.setUniform("backSideModelColor", backSideModelColor);
        program.setUniform("backSideDotColor", backSideDotColor);

        glm::vec3 lightInViewPos = viewMat * vec4(l->go->transform()->mPosition, 1.0f);
        glm::vec3 lightAmbient(1.0f, 1.0f, 1.0f);
        glm::vec3 lightDiffuse(1.0f, 1.0f, 1.0f);
        glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);
            
        program.setUniform("light.position", lightInViewPos);
        program.setUniform("light.ambient", lightAmbient);
        program.setUniform("light.diffuse", lightDiffuse);
        program.setUniform("light.specular", lightSpecular);

        program.setUniform("time", Time::sinceStart());
        
        glBindVertexArray(vao);
        
        glDrawArrays(drawType, 0, indexCount);
        
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
//
        
        
//        if(drawType == GL_LINES){
//            drawType = GL_TRIANGLES;
//        }else{
//            drawType = GL_LINES;
//        }
        
//        
//        if(direction > 0.0f){
//            direction = -2.0f;
//        }else{
//            direction = 2.0f;
//        }
        
        ++modelNum;
        modelNum = modelNum % 7;
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
