struct VS_Input
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct VS_Output
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

float4 main(VS_Output output) : SV_Target
{
    return output.color;
}