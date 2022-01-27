/***********************************************************************
 * Header File:
 *    Bird : Everything that can be shot
 * Author:
 *    Br. Helfrich, Journey Curtis (Implementation of Strategy pattern)
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once
#include "point.h"

// Enumeration to determine bird for factory!
enum BirdType{ STANDARD, SINKER, FLOATER, CRAZY };

/**********************
 * BIRD
 * Everything that can be shot
 **********************/
class Bird
{
protected:
   /****************************************************
    * BIRD :: ADVANCE CLASS
    * Advance contains two methods, factory and advance.
    * Factory returns the type of advance (for the 
    * respective bird). Advance is a virtual function
    * implemented by the type of advance.
    * NOTE. Implemented here because it kept giving me
    * errors in it's own file (circular dependancy).
    ***************************************************/
   class Advance {
   public:
      static Advance* factory(BirdType type) {
         switch (type) {
            case STANDARD:
               return new Bird::Inertia();
               break;
            case SINKER:
               return new Bird::Gravity();
               break;
            case FLOATER:
               return new Bird::Buoyancy();
               break;
            case CRAZY:
               return new Bird::Chaos();
               break;
         }
      }
      virtual void advance(Bird & bird) = 0;
   };
   
   /****************************************************
    * BIRD :: INTERTIA CLASS :: ADVANCE
    * Intertia inherits from Advance. It is the standard
    * bird's movement.
    ***************************************************/
   class Inertia: public Advance {
   public:
      void advance(Bird & bird);
   };

   /***************************************************
    * BIRD :: GRAVITY CLASS :: ADVANCE
    * Gravity inherits from Advance. It is the floater
    * bird's movement.
    **************************************************/
   class Gravity: public Advance {
   public:
      void advance(Bird & bird);
   };

   /****************************************************
    * BIRD :: BUOYANCY CLASS :: ADVANCE
    * Buoyancy inherits from Advance. It is the buoyancy
    * bird's movement.
    ***************************************************/
   class Buoyancy: public Advance {
   public:
      void advance(Bird & bird);
   };

   /**********************************************
    * BIRD :: CHAOS CLASS :: ADVANCE
    * Chaos inherits from Advance. It is the chaos
    * bird's movement.
    *********************************************/
   class Chaos: public Advance {
   public:
      void advance(Bird & bird);
   };
   
   static Point dimensions; // size of the screen
   Point pt;                  // position of the flyer
   Velocity v;                // velocity of the flyer
   double radius;             // the size (radius) of the flyer
   bool dead;                 // is this flyer dead?
   int points;                // how many points is this worth?
   Advance * a; // Pointer because it is an abstract class.
   
public:
   Bird() : dead(false), points(0), radius(1.0) { }
   
   // setters
   void operator=(const Point    & rhs) { pt = rhs;    }
   void operator=(const Velocity & rhs) { v = rhs;     }
   void kill()                          { dead = true; }

   // getters
   bool isDead()           const { return dead;   }
   Point getPosition()     const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   double getRadius()      const { return radius; }
   int getPoints() const { return points; }
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
              pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }

   // special functions
   virtual void draw() = 0;
   void advance() { a->advance(*this); }
   void adjustVelocity(float num) { v *= num; }
   void adjustPosition() { pt.add(v); }
   void subtractPoints() { points *= -1; }
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class Standard : public Bird
{
public:
    Standard(double radius = 25.0, double speed = 5.0, int points = 10);
    void draw();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class Floater : public Bird
{
public:
    Floater(double radius = 30.0, double speed = 5.0, int points = 15);
    void draw();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class Crazy : public Bird
{
public:
    Crazy(double radius = 30.0, double speed = 4.5, int points = 30);
    void draw();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class Sinker : public Bird
{
public:
    Sinker(double radius = 30.0, double speed = 4.5, int points = 20);
    void draw();
};
