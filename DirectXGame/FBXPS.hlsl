#include "FBX.hlsli"

//0�ԃX���b�g�ɐݒ肳�ꂽ�e�X�N�`��
Texture2D<float4> tex : register(to);
//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp : register(s0);
//�G���g���[�|�C���g
float4 main(VSOutput inout) : SV_TARAGET
{
	//�e�X�N�`���}�b�s���O
	float4 texcolor = tex.Sample(smp,input.uv);
	//Lambert����
	float3 light = normalize(float3(1, -1, 1)); //�E���������̃��C�g
	float diffuse = sarurate(dot(-light, input.nromal));
	float brightness = diffuse + 0.3f;
	float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);

	//�A�e�ƃe�X�N�`���̐F������
	return shadecolor * texcolor;
}