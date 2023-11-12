#version 330 core
in vec3 fDir;
in vec3 fPos;
in vec3 fUp;
in vec3 fRight;
in vec3 worldPos;


uniform sampler3D voxelShape;

out vec4 FragColor;

float maxcomp(in vec3 p ) { return max(p.x,max(p.y,p.z));}
float maxcomp(in vec2 p ) { return max(p.x,p.y);}

float mincomp(in vec3 p ) { return min(p.x,min(p.y,p.z));}


vec4 march(vec3 startPoint, vec3 dir)
{
  

  vec3 rayOrigin = startPoint;
  vec3 rayDirection = normalize(dir + (gl_FragCoord.x - 0.5) * fRight + (gl_FragCoord.y - 0.5) * fUp);

  float stepSize = 0.01; // Adjust this for ray marching precision
  float maxDistance = 20.0; // Maximum distance to march
  
  vec3 currentPosition = rayOrigin;
  float distanceTraveled = 0.0;
  
  for (int i = 0; i < 1000; i++) { // Perform a fixed number of steps to avoid infinite loops
      vec3 voxelPosition = currentPosition; // Convert ray position to voxel coordinates
      float voxelValue = texture(voxelShape, voxelPosition).r; // Access voxel data from the 3D texture
      
      if (voxelValue > 0.0) {
          // Voxel is solid, color the pixel
          return vec4(1.0, 0.0, 0.0, 1.0); // Red color (you can use the voxel data for color)
      }
      
      currentPosition += rayDirection * stepSize;
      distanceTraveled += stepSize;
      
      if (distanceTraveled >= maxDistance) {
          break; // Stop ray marching if we've traveled too far
      }
  }
  
  vec4 returnColor = vec4(0, 0, 0, 1.0);
  return returnColor;
}

float epsilon = 0.001;

vec4 PlaneMarch(vec3 p0, vec3 dir) {
  float t = 0;
  vec3 d = worldPos - p0;
  while (t <= 10.0) {
    vec3 p = p0 + d * t;
    vec4 c = texture(voxelShape, floor((p + 0.5)*10)/10);
    if (c.a > 0) {
      return c;
    }
    
    vec3 deltas = (step(0, d) - fract(p)) / d;
    t += max(mincomp(deltas), epsilon);
  }

  return vec4(0);
}


vec4 march2(vec3 camPos)
{
  float voxelSize = 0.1;
  vec3 currentPos = floor(worldPos*10 )/10; //Ranges from -0.5 to 0.5

  vec3 dir = worldPos - camPos;

  float stepX = (dir.x >= 0) ? 1.0 : -1.0;
  float stepY = (dir.y >= 0) ? 1.0 : -1.0;
  float stepZ = (dir.z >= 0) ? 1.0 : -1.0;


  float nextBoundryX = currentPos.x+stepX*voxelSize;
  float nextBoundryY = currentPos.y+stepY*voxelSize;
  float nextBoundryZ = currentPos.z+stepZ*voxelSize;

  float tMaxX = (nextBoundryX - worldPos.x)/dir.x;
  float tMaxY = (nextBoundryY - worldPos.y)/dir.y;
  float tMaxZ = (nextBoundryZ - worldPos.z)/dir.z;



  //float tMaxX = (currentPos.x - worldPos.x)/dir.x;
  //float tMaxY = (currentPos.y - worldPos.y)/dir.y;
  //float tMaxZ = (currentPos.z - worldPos.z)/dir.z;




  float tDeltaX = (voxelSize/dir.x)*stepX;
  float tDeltaY = (voxelSize/dir.y)*stepY;
  float tDeltaZ = (voxelSize/dir.z)*stepZ;


  int iterations = 0;
  while (true)
  {
    
    if (tMaxX < tMaxY) {
      if (tMaxX < tMaxZ) {
        currentPos.x += stepX*voxelSize;
        tMaxX += tDeltaX;
      } else {
        currentPos.z += stepZ*voxelSize;
        tMaxZ += tDeltaZ;
      }
    } else {
      if (tMaxY < tMaxZ) {
        currentPos.y += stepY*voxelSize;
        tMaxY += tDeltaY;
      } else {
        currentPos.z += stepZ*voxelSize;
        tMaxZ += tDeltaZ;
      }
    } 

    if (texture(voxelShape, currentPos+0.5).a > 0)
    {
      return vec4(texture(voxelShape, currentPos+0.5).rgb, 1.0);
     } 
    

    if (iterations > 100)
    {
      break;
    }
    if (currentPos.x < -0.5 || currentPos.x > 0.5 || currentPos.y < -0.5 || currentPos.y > 0.5 || currentPos.z < -0.5 || currentPos.z > 0.5) {
      break;
    }

    iterations++;
  }

  return vec4(0.0, 0.0, 0.0, 1.0);
}

vec4 march3(vec3 camPos, vec3 camDir)
{
  vec3 iResolution = vec3(800.0, 600.0, 0.0);
  vec2 screenPos = (gl_FragCoord.xy / iResolution.xy) * 2.0 - 1.0;
	vec3 cameraDir = worldPos - camPos;
	vec3 cameraPlaneU = vec3(1.0, 0.0, 0.0);
	vec3 cameraPlaneV = vec3(0.0, 1.0, 0.0) * iResolution.y / iResolution.x;
	vec3 rayDir = cameraDir + screenPos.x * cameraPlaneU + screenPos.y * cameraPlaneV;
	vec3 rayPos = worldPos;
		

	ivec3 mapPos = ivec3(floor(rayPos + 0.));

	vec3 deltaDist = abs(vec3(length(rayDir)) / rayDir);
	
	ivec3 rayStep = ivec3(sign(rayDir));

	vec3 sideDist = (sign(rayDir) * (vec3(mapPos) - rayPos) + (sign(rayDir) * 0.5) + 0.5) * deltaDist; 
	
	bvec3 mask;

  for (int i = 0; i < 100; i++) {
		if (texture(voxelShape, mapPos/10).a > 0) continue;

    //Thanks kzy for the suggestion!
    mask = lessThanEqual(sideDist.xyz, min(sideDist.yzx, sideDist.zxy));
    
    
    //All components of mask are false except for the corresponding largest component
    //of sideDist, which is the axis along which the ray should be incremented.			
    
    sideDist += vec3(mask) * deltaDist;
    mapPos += ivec3(vec3(mask)) * rayStep;

		
	}

  vec3 color;
	if (mask.x) {
		color = vec3(0.5);
	}
	if (mask.y) {
		color = vec3(1.0);
	}
	if (mask.z) {
		color = vec3(0.75);
	}




  return vec4(color, 1.0);
}


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

  if (camPos.x < 0.5 && camPos.x > -0.5 && camPos.y < 0.5 && camPos.y > -0.5 && camPos.z < 0.5 && camPos.z > -0.5)
  {
    rayPos = camPos;
  }


  vec3 rd = normalize(worldPos - camPos);
  vec3 pos = floor(rayPos*10+5);
  vec3 ri = 1.0/rd;
  vec3 rs = sign(rd);


  vec3 dis = (pos-(rayPos*10+5) + 0.5 + rs*0.5) * ri;
  vec3 mm = vec3(0.0);
 

  for (int i = 0; i < 128; i++)
  {
    
    if (texture(voxelShape, pos/10).a > 0 && !(pos.x == 10.0 || pos.y == 10.0 || pos.z == 10.0))
    {
      return vec4(texture(voxelShape, pos/10).rgb, 1.0);
    }


    mm = step(dis.xyz, dis.yzx) * step(dis.xyz, dis.zxy);
		dis += mm * rs * ri;
    pos += mm * rs;

    if (pos.x >= 10.0 || pos.x < 0.0 || pos.z >= 10.0 || pos.z < 0.0 || pos.y < 0.0 || pos.y >= 10.0)
    {
      break;
    }
  }

  return vec4(0.0);
}


void main()
{ 
  vec3 eyeNormal = normalize(fDir);

  vec4 color = march5(fPos);

  if (color.a == 0) {
    discard;
  }

 
  
  FragColor  = color;
}
