#include "Shader.h"

Shader::Shader()
{
    shader = 0;
    uniformModel = 0;
    uniformProjection = 0;

    pointLightCount = 0;
}

void Shader::CreateFromFiles(const char* vShader, const char* fShader)
{
    std::string vShaderCode = readShaderCodeFromFile(vShader);
    std::string fShaderCode = readShaderCodeFromFile(fShader);

    compileShaders(vShaderCode.c_str(), fShaderCode.c_str());
}

void Shader::SetDirectionalLight(DirectionalLight* theLight)
{
    theLight->useLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour, uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    glUniform1i(uniformPointLightCount, lightCount);

    for (size_t i = 0; i < lightCount; i++)
    {
        pLight[i].useLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour, 
            uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
            uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
    }

}

Shader::~Shader()
{
}

std::string Shader::readShaderCodeFromFile(const char* shaderPath)
{
    std::string code;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open shader file
        shaderFile.open(shaderPath);

        std::stringstream shaderStream;

        // read shader file buffer into the shaderstream string stream
        shaderStream << shaderFile.rdbuf();

        // save stream data to string output variable 'code'
        code = shaderStream.str();

        // close shader file
        shaderFile.close();
    }

    catch (std::ifstream::failure e) 
    {
        std::cout << "Shader file " << shaderPath << " cannot be read" << std::endl;
    }


    return code;
}

void Shader::addShader(unsigned int theProgram, const char* shaderCode, GLenum shaderType)
{
    unsigned int theShader = glCreateShader(shaderType);

    const char* theCode[1] = { shaderCode };

    int codeLength[1] = { (int)strlen(shaderCode) };

    glShaderSource(theShader, 1, theCode, codeLength);

    glCompileShader(theShader);

    int result = 0;
    char errorLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(errorLog), NULL, errorLog);
        std::cerr << "Error compiling the " << shaderType << " shader: '" << errorLog << "'\n";
        return;
    }

    glAttachShader(theProgram, theShader);
}

void Shader::compileShaders(const char* vShaderCode, const char* fShaderCode)
{
    shader = glCreateProgram();

    if (!shader)
    {
        std::cerr << "Error creating shader program\n";
        return;
    }

    addShader(shader, vShaderCode, GL_VERTEX_SHADER);
    addShader(shader, fShaderCode, GL_FRAGMENT_SHADER);

    int result = 0;
    char errorLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        std::cerr << "Error linking program: '" << errorLog << "'\n";

    }

    glValidateProgram(shader);

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        std::cerr << "Error validating program: '" << errorLog << "'\n";
        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");
    uniformProjection = glGetUniformLocation(shader, "projection");
    uniformView = glGetUniformLocation(shader, "view");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shader, "directionalLight.base.ambientIntensity");
    uniformDirectionalLight.uniformColour = glGetUniformLocation(shader, "directionalLight.base.colour");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shader, "directionalLight.base.diffuseIntensity");
    uniformDirectionalLight.uniformDirection = glGetUniformLocation(shader, "directionalLight.direction");
    uniformSpecularIntensity = glGetUniformLocation(shader, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shader, "material.shininess");
    uniformEyePosition = glGetUniformLocation(shader, "eyePosition");

    uniformPointLightCount = glGetUniformLocation(shader, "pointLightCount");

    for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        char LocBuff[100] = { '\0' };
        snprintf(LocBuff, sizeof(LocBuff), "pointLights[%d].base.colour", i);
        uniformPointLight[i].uniformColour = glGetUniformLocation(shader, LocBuff);

        snprintf(LocBuff, sizeof(LocBuff), "pointLights[%d].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shader, LocBuff);

        snprintf(LocBuff, sizeof(LocBuff), "pointLights[%d].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shader, LocBuff);

        snprintf(LocBuff, sizeof(LocBuff), "pointLights[%d].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shader, LocBuff);

        snprintf(LocBuff, sizeof(LocBuff), "pointLights[%d].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shader, LocBuff);

        snprintf(LocBuff, sizeof(LocBuff), "pointLights[%d].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shader, LocBuff);

        snprintf(LocBuff, sizeof(LocBuff), "pointLights[%d].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shader, LocBuff);
    }
}


