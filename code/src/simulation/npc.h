class NPC : public Positionable {
  private:
    Trajectory trajectory;
    float fear;
    bool shocked;
  public:
    float getFear();
    void setFear(float f);
    bool isShocked();
    void setShocked(bool s);
    void updateTrajectory(Trajectory t);
};
