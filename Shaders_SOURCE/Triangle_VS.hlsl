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


VS_Output main(VS_Input input)
{
    VS_Output output;
    output.position = float4(input.position, 1.0f);
    output.color = input.color;

    return output;
}