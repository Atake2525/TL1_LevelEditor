#include "Grayscale.PS.hlsl"

struct Vignette
{
    int enableVignette;
    float intensity; //!< �P�x
    float scale;
};
ConstantBuffer<Vignette> gVigentte : register(b1);

PixelShaderOutput ShadingVignetting(VertexShaderOutput input)
{
    PixelShaderOutput output;
    output = ShadingGrayscale(input); 
    //output.color = gTexture.Sample(gSampler, input.texcoord);
    
    if (gVigentte.enableVignette)
    {
         // ���͂�0�ɁA���S�ɂȂ�قǖ��邭�Ȃ�l�Ɍv�Z�Œ���
        float2 correct = input.texcoord * (1.0f - input.texcoord.yx * 1.0f);
        // correct�����Ōv�Z����ƒ��S�̍ő�l��0.0625�ňÂ�����̂�scale�Œ����B���̗�ł�16�{���ĂP�ɂ��Ă���
        float vignette = correct.x * correct.y * gVigentte.intensity;
        // �Ƃ肠����0.8��ł�����ۂ����Ă݂�
        vignette = saturate(pow(vignette, gVigentte.scale));
        // �W���Ƃ��ď�Z
        output.color.rgb *= vignette;
    }
    
    return output;
    
}

