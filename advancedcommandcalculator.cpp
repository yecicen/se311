#include <iostream>
#include <vector>
#define PI 3.14
using namespace std;
/*
**
    YUNUS EMRE ÇÝÇEN SE 311 2016 HOMEWORK 2
    I used Iterator, Composite and Command Designs to develop advanced calculator example.
**
/*
**
    Iterator Part
**
*/
class Collection;
class MacroCommand;
class MacroIterator;
class AbstractIterator
{
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual MacroCommand* CurrentItem() const = 0;
};
class MacroIterator:public AbstractIterator
{
private:
    Collection* _MacroCollection;
    int current;
public:
    MacroIterator( Collection* MacroCollection);
    void First();
    void Next();
    bool IsDone() const;
    MacroCommand* CurrentItem() const;
};
/*
**
    End of Iterator Part
**
*/
/*
**Collection Part
*/
class AbstractAggregate
{
protected:
    AbstractAggregate() {};
public:
    virtual ~AbstractAggregate() {};
    virtual AbstractIterator* CreateIterator() = 0;
    virtual void add(MacroCommand*) = 0;
    virtual int getCount() const = 0;
    virtual MacroCommand * get(int) const = 0;
};
class Collection: public AbstractAggregate
{
private:
    vector<MacroCommand*> command;
public:
    MacroIterator* CreateIterator()
    {
        return new MacroIterator(this);
    }
    void add(MacroCommand* _command)
    {
        command.push_back(_command);
    }
    int getCount() const
    {
        return command.size();
    }
    MacroCommand *get(int index) const
    {
        return command[index];
    }
};
MacroIterator::MacroIterator( Collection* MacroCollection):_MacroCollection(MacroCollection), current(0) {}
void MacroIterator::First()
{
    current = 0;
}
void MacroIterator::Next()
{
    current++;
}
bool MacroIterator::IsDone() const
{
    return current >= _MacroCollection->getCount();
}
MacroCommand* MacroIterator::CurrentItem() const
{
    return IsDone()?NULL:_MacroCollection->get(current);
}
/*
**
    End of Collection Part
**
*/
/*
**
    Calculator Part
**
*/
class Calculator
{
public:
    Calculator() : current_value(0) {};
    void Action(char _operator, int operand)
    {
        switch(_operator)
        {
        case '+':
            current_value += operand;
            break;
        case '-':
            current_value -= operand;
            break;
        case '*':
            current_value *= operand;
            break;
        case '/':
            current_value /= operand;
            break;
        case '@':
            current_value = 2*PI*operand;
            break;
        case '$': current_value = 1/(2*PI);
        }
        cout << "Current value " << current_value << " (following "
             << _operator << " " << operand << ")" << endl;
    }
    bool GreaterThan(int operand_1, int operand2_)
    {
        if(operand2_ > operand_1)
            return true;
        else return false;
    }
    bool LessThan(int operand_1, int operand_2)
    {
        if(operand_1<operand_2)
            return true;
        else return false;
    }
    bool EqualTo(int operand_1, int operand_2)
    {
        if(operand_1 == operand_2)
            return true;
        else return false;
    }
    void LogicAction(char _operator,int operand1, int operand2)
    {
        switch(_operator)
        {
        case '>':
            GreaterThan(operand1,operand2);
        case '<':
            LessThan(operand1,operand2);
        case '=':
            EqualTo(operand1,operand2);
        }
    }
private:
    int current_value;
};
class Command
{
public:
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
protected:
    Command() {};
};
/*
*
*Class MacroCommand
*
*/
class MacroCommand:public Command
{
private:
    Calculator* _calculator;
    char _operator = '@';
    int _radius;
    char Undo(char _operator)
    {
        switch (_operator)
        {
        case '@':
            return '$';
            break;
        default :
            return ' ';
            break;
        }
    }
public:
    MacroCommand(Calculator *calculator, int radius)
        : _calculator(calculator), _radius(radius) {}
    void Execute()
    {
        _calculator->Action(_operator, _radius);
    }
    void UnExecute()
    {
        _calculator->Action(Undo(_operator), _radius);
    }
};
class Circumference:public MacroCommand
{

};
//
// "Arithmetic"
//
class Arithmetic:public Command
{
public:
    Arithmetic():Command() {};
};
class Summation: public Arithmetic
{
private:
    Calculator*	_calculator;
    char 		_operator = '+';
    int 		_operand;
    char Undo(char _operator)
    {
        switch (_operator)
        {
        case '+':
            return '-';
        default :
            return ' ';
        }
    }
public:
    Summation(Calculator *calculator, int operand)
        : _calculator(calculator), _operand(operand) {}
    void Execute()
    {
        _calculator->Action(_operator, _operand);
    }
    void UnExecute()
    {
        _calculator->Action(Undo(_operator), _operand);
    }
};
class Difference:public Arithmetic
{
private:
    Calculator*	_calculator;
    char 		_operator='-';
    int 		_operand;
    char Undo(char _operator)
    {
        switch (_operator)
        {
        case '-':
            return '+';
        default :
            return ' ';
        }
    }
public:
    Difference(Calculator *calculator,  int operand)
        : _calculator(calculator), _operand(operand) {}
    void Execute()
    {
        _calculator->Action(_operator, _operand);
    }
    void UnExecute()
    {
        _calculator->Action(Undo(_operator), _operand);
    }
};
class Multipication:public Arithmetic
{
private:
    Calculator*	_calculator;
    char 		_operator = '*';
    int 		_operand;
    char Undo(char _operator)
    {
        switch (_operator)
        {
        case '*':
            return '/';
        default :
            return ' ';
        }
    }
public:
    Multipication(Calculator *calculator, int operand)
        : _calculator(calculator), _operand(operand) {}
    void Execute()
    {
        _calculator->Action(_operator, _operand);
    }
    void UnExecute()
    {
        _calculator->Action(Undo(_operator), _operand);
    }
};
class Division:public Arithmetic
{
private:
    Calculator*	_calculator;
    char 		_operator = '/';
    int 		_operand;
    char Undo(char _operator)
    {
        switch (_operator)
        {
        case '/':
            return '*';
        default :
            return ' ';
        }
    }
public:
    Division(Calculator *calculator, int operand)
        : _calculator(calculator),  _operand(operand) {}
    void Execute()
    {
        _calculator->Action(_operator, _operand);
    }
    void UnExecute()
    {
        _calculator->Action(Undo(_operator), _operand);
    }
};

class Logical: public Command
{
public:
    Logical():Command() {};
};
class Greater:public Logical
{
private:
    int operand1;
    int operand2;
    char _operator='>';
    Calculator *_calculator;
public:
    void Execute()
    {
        _calculator->LogicAction(_operator,operand1,operand2);
    };
    void UnExecute()
    {
        cout << "Meaningless Command" << endl;
    };
};
class Smaller: public Logical
{
private:
    int operand1;
    int operand2;
    char _operator='<';
    Calculator *_calculator;
public:
    void Execute()
    {
        _calculator->LogicAction(_operator,operand1,operand2);
    };
    void UnExecute()
    {
        cout << "Meaningless Command" << endl;
    };
};
class Equal: public Logical
{
private:
    int operand1;
    int operand2;
    char _operator='>';
    Calculator *_calculator;
public:
    void Execute()
    {
        _calculator->LogicAction(_operator,operand1,operand2);
    };
    void UnExecute()
    {
        cout << "Meaningless Command" << endl;
    };
};

//
// "ConcreteCommand"
//
class CalculatorCommand : public Command
{
public:
    // Constructor
    CalculatorCommand(Calculator *calculator, char op, int operand)
        : _calculator(calculator), _operator (op), _operand(operand) {}
    void Execute()
    {
        _calculator->Action(_operator, _operand);
    }
    void UnExecute()
    {
        _calculator->Action(Undo(_operator), _operand);
    }
    // Private helper function. Needed to get the inverse operation.
private:
    char Undo(char _operator)
    {
        switch (_operator)
        {
        case '+':
            return '-';
        case '-':
            return '+';
        case '*':
            return '/';
        case '/':
            return '*';
        default :
            return ' ';
        }
    }
    Calculator*	_calculator;
    char 		_operator;
    int 		_operand;
};

// "Invoker"
class User
{
public:
    User(): current(0) {};
    void Redo(int levels)
    {
        cout << "\n---- Redo " << levels << " levels " << endl;
        // Perform redo operations
        for (int i = 0; i < levels; i++)
        {
            if (current < _commands.size())
            {
                Command *command = _commands[current++];
                command->Execute();
            }
        }
    }
    void Undo(int levels)
    {
        cout << "\n---- Undo " << levels << " levels " << endl;
        // Perform undo operations
        for (int i = 0; i < levels; i++)
        {
            if (current > 0)
            {
                Command *command = _commands[--current];
                command->UnExecute();
            }
        }
    }
    void Compute(Command *command)
    {
        command->Execute();
        // Add command to undo list
        _commands.push_back(command);
        current++;
    }
private:
    // Initializers.
    Calculator			*_calculator;
    vector<Command *>	_commands;
    unsigned int 				current;
};

int main()
{
    Calculator* calculator = new Calculator();
    User* user = new User();
    AbstractAggregate* collection = new Collection();
    collection->add(new MacroCommand(calculator,10));

    AbstractIterator* Macro_Iterator = collection->CreateIterator();
    MacroCommand* command = collection->get(0);
    user->Compute(command);

    user->Undo(1);
}
