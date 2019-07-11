//Files with predefined colors and textures
#include "colors.inc"
#include "glass.inc"
#include "golds.inc"
#include "metals.inc"
#include "stones.inc"
#include "woods.inc"

//Place the camera
camera {
  sky <0,0,1>          //Don't change this
  direction <-1,0,0>   //Don't change this  
  right <-4/3,0,0>     //Don't change this
  //location  <30,10,10>  //Camera location
    location <5090, 5090, 5090>
  look_at   <0,0,0>    //Where camera is pointing
  angle 2      //Angle of the view--increase to see more, decrease to see less
}

//Ambient light to "brighten up" darker pictures
global_settings { ambient_light White }

//Place a light--you can have more than one!
light_source {
  <310,-10,310>   //Change this if you want to put the light at a different point
  color White*2        //Multiplying by 2 doubles the brightness
}

//Set a background color
background { color White }

//Create a "floor"
plane {
  <0,0,1>, 0           //This represents the plane 0x+0y+z=0
  texture { T_Brass_3A }  //The texture comes from the file "metals.inc"
}

