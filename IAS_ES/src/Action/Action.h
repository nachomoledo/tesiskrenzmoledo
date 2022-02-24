#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
   virtual void execute(void) = 0;
   virtual ~Action()= default;
};

#endif // ACTION_H
