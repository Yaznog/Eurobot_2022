class Coordinate_Calculator
{
  public:
  
    Coordinate_Calculator(unsigned int leg_Mid_Length, unsigned int leg_Bot_Length);

    void set_Leg_Top_Length(unsigned int length_Value);
    void set_Leg_Mid_Length(unsigned int length_Value);
    void set_Leg_Bot_Length(unsigned int length_Value);

    unsigned int get_Leg_Top_Length();
    unsigned int get_Leg_Mid_Length();
    unsigned int get_Leg_Bot_Length();

    float get_X_Coordinate();
    float get_Y_Coordinate();
    float get_Z_Coordinate();
    float get_Module_Coordinate();
    float get_Argument_Coordinate();

    void set_Coordinate_Target(float x, float y, float z);
    void set_Coordinate_Polar_Target(float module, float argument, float z);

    float get_Servo_Top_Angle();
    float get_Servo_Mid_Angle();
    float get_Servo_Bot_Angle();
   
  private:

    unsigned int m_Leg_Top_Length;
    unsigned int m_Leg_Mid_Length;
    unsigned int m_Leg_Bot_Length;
    
    float m_X_Coordinate;
    float m_Y_Coordinate;
    float m_Z_Coordinate;
    float m_Module_Coordinate;
    float m_Argument_Coordinate;
    
 
};
