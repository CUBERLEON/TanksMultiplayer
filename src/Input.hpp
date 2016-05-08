#ifndef INPUT_HPP
#define INPUT_HPP

class Input {
public:
    enum Keyboard {
        A = 0,
        W,
        S,
        D,
        KEYBOARD_CNT
    };
    enum Mouse {
        Left = 0,
        Right,
        MOUSE_CNT
    };
    
    virtual ~Input();
    
    int getKeyboardKeyState(unsigned int key) const { return m_keyboard[key]; }
    int getMouseKeyState(unsigned int key) const { return m_mouse[key]; }
protected:
    Input();

    int* m_keyboard;
    int* m_mouse;
    
    virtual void update() = 0;
private:
};

#endif