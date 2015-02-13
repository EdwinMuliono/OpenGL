#version 410

in vec4 vNormal;
in vec4 vPosition;
out vec4 FragColor;

uniform vec3 light_dir;
uniform vec3 light_color;

uniform vec3 material_color;
uniform vec3 ambient_light;

uniform vec3 CamPos;
uniform float SpecPower;

void main()
{
	vec3 Ambient = material_color * ambient_light;

	vec3 normal = normalize(vNormal.xyz);
	vec3 light = normalize(light_dir);
	
	float d = dot(normal, -light);
	d = max(d, 0);

	vec3 FinalDiffuse = vec3(d) * light_color * material_color;

	vec3 E = normalize(CamPos - vPosition.xyz);
	vec3 R = reflect(light, normal);

	float s = dot(R, E);
	s = pow(s, SpecPower);
	vec3 Spec = vec3(s) * light_color * material_color;

	FragColor = vec4(Ambient + FinalDiffuse + Spec, 1);
}