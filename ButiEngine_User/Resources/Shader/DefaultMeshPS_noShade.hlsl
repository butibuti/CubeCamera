#include"DefaultShader.hlsli"
float4 PSMain(Pixel_UV_Normal pixel) : SV_TARGET
{
	float4 Tex = (mainTexture.Sample(mainSampler,pixel.uv).rgba);
	
	
	return  float4((Tex).rgb*lightDir.rgb, Tex.a);
}