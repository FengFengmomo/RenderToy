#include "Model.h"

Model::Model()
{
    m_Name = "Default";
    m_Position = glm::vec3(0.0f);
    m_Scale = glm::vec3(1.0f);
    m_EulerAngle = glm::vec3(0.0f);
}

Model::~Model()
{
}

void Model::Init()
{
    spdlog::info("Compiling model shader from: " + m_ShaderPath);
    if (m_Shader.Init(m_ShaderPath))
    {
        spdlog::info("Shader Compiled.");
    }
    else
    {
        spdlog::warn("Failed to compile shader.");
    }
    
}

bool Model::LoadModel(std::string modelPath, std::string shaderPath)
{
    m_ShaderPath = shaderPath;
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::string errorMsg = "ERROR::ASSIMP::" + std::string(import.GetErrorString());
        spdlog::error(errorMsg);
        return false;
    }
    m_Directory = modelPath.substr(0, modelPath.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
    spdlog::info("Model loaded");
    return true;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    glm::vec3 vector;
    
    //Process each vertex
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        //Get the position of the vertex
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.m_Position = vector;
        //Get the normal of the vertex
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.m_Normal = vector;
        
        //Get the texture coord of the vertex
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.m_TexCoords = vec;
        }
        else
        {
            vertex.m_TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    //Process the indicies of each vertex
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    //Process each texture
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 
    // 1. Diffuse maps
    std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "tex_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. Specular maps
    std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "tex_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. Normal maps
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "tex_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. Height maps
    //std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        //Check if a texture was already loaded. If it did, skip. If it didn't, load texture.
        bool skip = false;
        for (unsigned int j = 0; j < m_Textures.size(); j++)
        {
            if (std::strcmp(m_Textures[j].GetFilePath().data(), str.C_Str()) == 0)
            {
                textures.push_back(m_Textures[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {   
            // if texture hasn't been loaded already, load it
            std::string filepath = GetDirectory() + '/' + std::string(str.C_Str());
            Texture texture(filepath, typeName);
            textures.push_back(texture);
            m_Textures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
        }
    }
    return textures;
}

void Model::SetPosX(float posX)
{
    m_Position.x = posX;
}

float Model::GetPosX() const
{
    return m_Position.x;
}

void Model::SetPosY(float posY)
{
    m_Position.y = posY;
}

float Model::GetPosY() const
{
    return m_Position.y;
}

void Model::SetPosZ(float posZ)
{
    m_Position.z = posZ;
}

float Model::GetPosZ() const
{
    return m_Position.z;
}

void Model::SetPos(float posX, float posY, float posZ)
{
    m_Position = glm::vec3(posX, posY, posZ);
}

void Model::SetScaleX(float scaleX)
{
    m_Scale.x = scaleX;
}

float Model::GetScaleX()
{
    return m_Scale.x;
}

void Model::SetScaleY(float scaleY)
{
    m_Scale.y = scaleY;
}

float Model::GetScaleY()
{
    return m_Scale.y;
}

void Model::SetScaleZ(float scaleZ)
{
    m_Scale.z = scaleZ;
}

float Model::GetScaleZ()
{
    return m_Scale.z;
}

void Model::SetScale(float scaleX, float scaleY, float scaleZ)
{
    m_Scale = glm::vec3(scaleX, scaleY, scaleZ);
}

void Model::SetPitch(float pitch)
{
    if (abs(pitch) > 360.0f)
    {
        pitch -= pitch;
    }
    m_EulerAngle.x = pitch;
}

float Model::GetPitch() const
{
    return m_EulerAngle.x;
}

void Model::SetYaw(float yaw)
{
    if (abs(yaw) > 360.0f)
    {
        yaw -= yaw;
    }
    m_EulerAngle.y = yaw;
}

float Model::GetYaw() const
{
    return m_EulerAngle.y;
}

void Model::SetRoll(float roll)
{
    if (abs(roll) > 360.0f)
    {
        roll -= roll;
    }
    m_EulerAngle.z = roll;
}

float Model::GetRoll() const
{
    return m_EulerAngle.z;
}

void Model::SetRot(float pitch, float yaw, float roll)
{
    if (abs(pitch) > 360.0f)
    {
        pitch -= pitch;
    }
    if (abs(yaw) > 360.0f)
    {
        yaw -= yaw;
    }
    if (abs(roll) > 360.0f)
    {
        roll -= roll;
    }
    m_EulerAngle = glm::vec3(pitch, yaw, roll);
}

void Model::SetModelName(std::string modelName)
{
    m_Name = modelName;
}

glm::mat4 Model::GetPosMat()
{
    glm::mat4 modelPos = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));
    return modelPos;
}

glm::mat4 Model::GetScaleMat()
{
    glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), m_Scale);
    return modelScale;
}

glm::mat4 Model::GetRotMat()
{
    glm::qua<float> quaternion = glm::qua<float>(glm::radians(m_EulerAngle));
    glm::mat4 modelRot = glm::mat4_cast(quaternion);
    return modelRot;
}

glm::mat4 Model::GetModelMat()
{
    glm::mat4 modelPos = glm::translate(glm::mat4(1.0f), m_Position);
    //glm::qua<float> quaternion = glm::qua<float>(glm::radians(glm::vec3(m_EulerAngle.x, m_EulerAngle.z, m_EulerAngle.y)));
    //glm::mat4 modelRot = glm::mat4_cast(quaternion);
    glm::mat4 modelRot = glm::rotate(glm::mat4(1.0f), glm::radians(m_EulerAngle.y), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_EulerAngle.x), glm::vec3(1, 0, 0));
    glm::vec4 axis = modelRot * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    modelRot = core::GetRodrigue(glm::normalize(axis), m_EulerAngle.z) * modelRot;
    glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), m_Scale);
    glm::mat4 model = modelPos * modelRot * modelScale;
    return model;
}

std::vector<Mesh>& Model::GetMeshes()
{
    return m_Meshes;
}

std::string Model::GetDirectory()
{
    return m_Directory;
}

Shader& Model::GetShader()
{
    return m_Shader;
}

void Model::GetUI()
{
    ImGui::PushItemWidth(60);
    ImGui::InputFloat("Pos X", &m_Position.x); ImGui::SameLine();  
    ImGui::InputFloat("Pos Y", &m_Position.y); ImGui::SameLine();
    ImGui::InputFloat("Pos Z", &m_Position.z);
    ImGui::PushItemWidth(60);
    ImGui::InputFloat("Scale X", &m_Scale.x); ImGui::SameLine();
    ImGui::InputFloat("Scale Y", &m_Scale.y); ImGui::SameLine();
    ImGui::InputFloat("Scale Z", &m_Scale.z);
    ImGui::PushItemWidth(200);
    ImGui::SliderFloat("Pitch", &m_EulerAngle.x, -360.0f, 360.0f);
    ImGui::SliderFloat("Yaw", &m_EulerAngle.y, -360.0f, 360.0f);
    ImGui::SliderFloat("Roll", &m_EulerAngle.z, -360.0f, 360.0f);
    if (ImGui::Button("reset"))
    {
        m_Position = glm::vec3(0.0f);
        m_EulerAngle = glm::vec3(0.0f);
        m_Scale = glm::vec3(1.0f);
    }
}