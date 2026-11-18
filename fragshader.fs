#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform vec2 iRes;
uniform float time;
uniform vec3 camerapos;
uniform float yaw;
uniform float pitch;
uniform int locked;

vec3 palette(float t){

    vec3 a = vec3(1, 0.5, 1);
    vec3 b = vec3(0.7, 0.9, 0.8);
    vec3 c = vec3(0.52, 0.780, 0.19);
    vec3 d = vec3(0.11, 0, 0.81);

    float k = 1;
    if(locked==1){k = sin(time/2)*2;}


    return a - b * cos(1.271  * k * (c * t + d));

}



float sdHexPrism( vec3 p, vec2 h )
{
  const vec3 k = vec3(-0.8660254, 0.5, 0.57735);
  p = abs(p);
  p.xy -= 2.0*min(dot(k.xy, p.xy), 0.0)*k.xy;
  vec2 d = vec2(
       length(p.xy-vec2(clamp(p.x,-k.z*h.x,k.z*h.x), h.x))*sign(p.y-h.x),
       p.z-h.y );
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}



float map(vec3 p){

    vec3 q = p;
    p.z += 0.5 * time;
    q.xy = fract(p.xy) - 0.5;
    q.z = mod(p.z, 0.25)- sin(time)*0.1/4;
    vec2 h = vec2(0.05,0.05);
    float box = sdHexPrism(q,h);
    

    return box;

}


void main(){
    vec2 fragCoord = vec2(fragTexCoord.x, 1.0 - fragTexCoord.y) * iRes;
    vec2 uv = ( fragCoord* 2.0 - iRes.xy) / iRes.y;
    vec3 ro = camerapos;

    float cp = cos(pitch), sp = sin(pitch);
    float cy = cos(yaw), sy = sin(yaw);
    vec3 forward = vec3(sy * cp, sp, cy * cp);
    vec3 right = normalize(cross(vec3(0.0, 1.0, 0.0), forward));
    vec3 up = cross(forward, right);

    vec3 rd = normalize(forward + uv.x * right + uv.y * up);
    vec3 col = vec3(0);
    float total_dist = 0;
    int i = 0;
    for(i=0; i < 80; ++i){
        
        vec3 p = ro+ rd * total_dist;
        p.y += sin(total_dist)*0.65;

        float d = map(p);
        total_dist += d;

        if(total_dist > 100.0 || d < 0.01)break;

    }

    col = palette(total_dist*0.4*(float(i)/20));

    finalColor = vec4(col,1);

}
