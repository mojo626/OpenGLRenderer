#version 330 core
in vec3 fPos;
in vec3 worldPos;
in vec3 cubePos;


uniform sampler3D voxelShape;

out vec4 FragColor;

float maxcomp(in vec3 p ) { return max(p.x,max(p.y,p.z));}
float maxcomp(in vec2 p ) { return max(p.x,p.y);}

float mincomp(in vec3 p ) { return min(p.x,min(p.y,p.z));}



float epsilon = 0.001;


vec4 march4(vec3 camPos)
{
  vec3 dir = normalize(worldPos - camPos);

  float step = 0.001f;
  vec3 currentPos = worldPos;


  if (camPos.x > -0.5 && camPos.x < 0.5 && camPos.y > -0.5 && camPos.y < 0.5 && camPos.z > -0.5 && camPos.z < 0.5)
  {
    currentPos = camPos;
  }


  for (int i = 0; i < 2000; i++)
  {
    currentPos += dir * step;

    if (currentPos.x > 0.5f || currentPos.x < -0.5f || currentPos.y > 0.5f || currentPos.y < -0.5f || currentPos.z > 0.5f || currentPos.z < -0.5f)
    {
      return vec4(0.2, 0.3, 0.3, 1.0);
    }

    if (texture(voxelShape, floor((currentPos + 0.5)*10)/10).a > 0)
    {
      return vec4(texture(voxelShape, floor((currentPos + 0.5)*10)/10).rgb, 1.0);
    }
  }

  return vec4(0.2, 0.3, 0.3, 1.0);
}

vec4 march5(vec3 camPos)
{
  vec3 rayPos = worldPos;

  if (camPos.x - cubePos.x < 0.5 && camPos.x - cubePos.x > -0.5 && camPos.y - cubePos.y < 0.5 && camPos.y - cubePos.y > -0.5 && camPos.z - cubePos.z < 0.5 && camPos.z - cubePos.z > -0.5)
  {
    rayPos = camPos - cubePos;
  }


  vec3 rd = normalize(worldPos + cubePos - camPos);
  vec3 pos = floor((rayPos)*10+5);
  vec3 ri = 1.0/rd;
  vec3 rs = sign(rd);


  vec3 dis = (pos-((rayPos)*10+5) + 0.5 + rs*0.5) * ri;
  vec3 mm = vec3(0.0);
  vec4 col = vec4(0.0);
 

  for (int i = 0; i < 128; i++)
  {
    
    if (texture(voxelShape, (pos)/10).a > 0 && !(pos.x == 10.0 || pos.y == 10.0 || pos.z == 10.0))
    {
      col = vec4(texture(voxelShape, (pos)/10).rgb, 1.0);
      break;
    }


    mm = step(dis.xyz, dis.yzx) * step(dis.xyz, dis.zxy);
		dis += mm * rs * ri;
    pos += mm * rs;

    if (pos.x >= 10.0 || pos.x < 0.0 || pos.z >= 10.0 || pos.z < 0.0 || pos.y < 0.0 || pos.y >= 10.0)
    {
      break;
    }
  }

  vec3 nor = -mm*rs;
  float test = dot(nor, rd);

  return col * (test + 1)/2;
}


void main()
{ 


  vec4 color = march5(fPos);

  if (color.a == 0) {
    discard;
  }

 
  
  FragColor  = color;
}
