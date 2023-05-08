class Ball;

class Collider
{
public:
    virtual void collideWith(Ball* ball) {}
    virtual float timeToCollision(Ball* ball) {}
    virtual bool getIsDeleted() const { return isDeleted; }
    bool isDeleted = false;
};