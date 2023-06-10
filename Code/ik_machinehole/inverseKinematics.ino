float T[4][4];
void IK(float pos[4],float oreintation[3]){
  //float pos[] = {x,y,z,1};
  //float oreintation[] = {theta,phi,psi};
  float R = 100;
  float r = 30;
  float r11 = cos(oreintation[1])*cos(oreintation[0]);
  float r12 = cos(oreintation[1])*sin(oreintation[0])*sin(oreintation[2])-sin(oreintation[1])*cos(oreintation[2]);
  float r13 = cos(oreintation[1])*sin(oreintation[0])*cos(oreintation[2])+sin(oreintation[1])*sin(oreintation[2]);
  
  float r21 = sin(oreintation[1])*cos(oreintation[0]);
  float r22 = sin(oreintation[1])*sin(oreintation[0])*sin(oreintation[2])+cos(oreintation[1])*cos(oreintation[2]);
  float r23 = sin(oreintation[1])*sin(oreintation[0])*cos(oreintation[2])-cos(oreintation[1])*sin(oreintation[2]);
  
  float r31 = -sin(oreintation[0]);
  float r32 = cos(oreintation[0])*sin(oreintation[2]);
  float r33 = cos(oreintation[0])*cos(oreintation[2]);

  float T[][4] = { {r11, r12, r13, pos[0]},
        {r21, r22, r23, pos[1]},
        {r31, r32, r33, pos[2]},
        {  0,   0,   0,      1}};
        
  float  a[0][4]= {{R*cos(radians(30))},
         {-R*sin(radians(30))},
                        {0},
                        {1}};

  float a[1]= {{-R*cos(radians(30))},
         {-R*sin(radians(30))},
         {0},
         {1}};
  
  float a[2]= {{0},
         {R},
         {0},
         {1}};
  
  float b[0][4]= {{ r*cos(radians(30))},
                  {-r*sin(radians(30))},
                                    {0},
                                    {1}};
  
  float b[1]= {{-r*cos(radians(30))},
         {-r*sin(radians(30))},
                       {0},
                       {1}};
  
  float b[2]= {{0},
         {r},
         {0},
         {1}};  
  
  for(int i = 0; i < 3; i++){
      float s[i] = multiply(T,b[i]) ;
      float s_[i] = subtract(s[i] - a[i]);
      float ans[i] = (sqrt(np.square(s[i][0])+np.square(s[i][1])+np.square(s[i][2])));
      float r_ans[i] = (sqrt(np.square(s_[i][0])+np.square(s_[i][1])+np.square(s_[i][2])));      

  }
  int activate = 0;
  
  for(int i = 0; i < 3; i++):
      if (ans[i] > max_limit or ans[i]< min_limit){
          print("configuration not possible please try again");
          activate = 0;
          break;
          }
      else
          activate = 1;
}
