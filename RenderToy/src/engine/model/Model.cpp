#include "Model.h"

Model::Model()
{
    VertexArray va();
    VertexBuffer vb();
    IndexBuffer ib();
    posX = 0.0f;
    posY = 0.0f;
    posZ = 0.0f;
    pitch = 0.0f;
    yaw = 0.0f;
    roll = 0.0f;
}

Model::~Model()
{
}

void Model::Init()
{
    //positions of every vertex
    float cube[] = {
       -5.0f, -5.0f, -5.0f, 0.25f, 0.33f, //0
        5.0f, -5.0f, -5.0f, 0.50f, 0.33f, //1
        5.0f,  5.0f, -5.0f, 0.50f, 0.66f, //2
       -5.0f,  5.0f, -5.0f, 0.25f, 0.66f, //3 near
       -5.0f, -5.0f,  5.0f, 0.75f, 0.33f, //4
        5.0f, -5.0f,  5.0f, 1.00f, 0.33f, //5
        5.0f,  5.0f,  5.0f, 1.00f, 0.66f, //6
       -5.0f,  5.0f,  5.0f, 0.75f, 0.66f, //7 far
       -5.0f, -5.0f,  5.0f, 0.00f, 0.33f, //8
       -5.0f, -5.0f, -5.0f, 0.25f, 0.33f, //9
       -5.0f,  5.0f, -5.0f, 0.25f, 0.66f, //10
       -5.0f,  5.0f,  5.0f, 0.00f, 0.66f, //11 left
        5.0f, -5.0f, -5.0f, 0.50f, 0.33f, //12
        5.0f, -5.0f,  5.0f, 0.75f, 0.33f, //13
        5.0f,  5.0f,  5.0f, 0.75f, 0.66f, //14
        5.0f,  5.0f, -5.0f, 0.50f, 0.66f, //15 right
       -5.0f,  5.0f, -5.0f, 0.25f, 0.66f, //16
        5.0f,  5.0f, -5.0f, 0.50f, 0.66f, //17
        5.0f,  5.0f,  5.0f, 0.50f, 1.00f, //18
       -5.0f,  5.0f,  5.0f, 0.25f, 1.00f, //19 top
       -5.0f, -5.0f,  5.0f, 0.25f, 0.00f, //20
        5.0f, -5.0f,  5.0f, 0.50f, 0.00f, //21
        5.0f, -5.0f, -5.0f, 0.50f, 0.33f, //22
       -5.0f, -5.0f, -5.0f, 0.25f, 0.33f  //23 bottom
    };

    //indicate the vertex of each triangle
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        8, 9, 10,
        10, 11, 8,
        12, 13, 14,
        14, 15 ,12,
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };

    VertexBufferLayout layout;
    va.GenVertexArray();
    vb.GenVertexBuffer(cube, sizeof(cube));
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    ib.GenIndexBuffer(indices, (unsigned int)(sizeof(indices) / sizeof(unsigned int)));
}

VertexArray& Model::GetVertexArray()
{
	return va;
}

IndexBuffer& Model::GetIndexBuffer()
{
	return ib;
}

glm::mat4 Model::GetModelMat()
{
	return model;
}

void Model::SetPosX(float setPosX)
{
    posX = setPosX;
}

float Model::GetPosX()
{
    return posX;
}

void Model::SetPosY(float setPosY)
{
    posY = setPosY;
}

float Model::GetPosY()
{
    return posY;
}

void Model::SetPosZ(float setPosZ)
{
    posZ = setPosZ;
}

float Model::GetPosZ()
{
    return posZ;
}

void Model::SetPos(float setPosX, float setPosY, float setPosZ)
{
    posX = setPosX;
    posY = setPosY;
    posZ = setPosZ;
}

glm::mat4 Model::GetPos()
{
    glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
    return cameraPos;
}

void Model::SetPitch(float setPitch)
{
    pitch = setPitch;
}

float Model::GetPitch()
{
    return pitch;
}

void Model::SetYaw(float setYaw)
{
    yaw = setYaw;
}

float Model::GetYaw()
{
    return yaw;
}

void Model::SetRoll(float setRoll)
{
    roll = setRoll;
}

float Model::GetRoll()
{
    return roll;
}

void Model::SetRot(float setPitch, float setYaw, float setRoll)
{
    pitch = setPitch;
    yaw = setYaw;
    roll = setRoll;
}
