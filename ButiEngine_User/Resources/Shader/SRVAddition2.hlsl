#include"DefaultShader.hlsli"

#define Distortion	0.125
float4 PSMain(Pixel_UV pixel) : SV_TARGET
{
	float2 samplePoint = pixel.uv;
	samplePoint -= float2(0.5, 0.5);
	float distPower = pow(length(samplePoint), Distortion);
	samplePoint *= float2(distPower,distPower);
	samplePoint += float2(0.5 , 0.5);


    float4 output = mainTexture.Sample(mainSampler, samplePoint) + subTexture_1.Sample(mainSampler, samplePoint)*lightDir.w;

	float vignette = length(float2(0.5, 0.5) - pixel.uv);

	vignette = clamp(vignette - 0.2, 0, 1);
	output.rgb -= vignette;
    output.w = 1.0f;
    return output;
}