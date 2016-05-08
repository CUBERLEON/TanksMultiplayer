#ifndef INPUT_HPP
#define INPUT_HPP

class Input {
public:
    static enum Keyboard {
        A = 0,
        W,
        S,
        D,
        Escape,
        KEYS_CNT
    };
    static enum Mouse {
        Left = 0,
        Right,
        KEYS_CNT
    };
    
    Input();
    ~Input();

    void update();
    
    int getKeyboardKeyState(unsigned int key) const { return m_keyboard[key]; }
    int getMouseKeyState(unsigned int key) const { return m_mouse[key]; }
protected:
private:
    int* m_keyboard;
    int* m_mouse;
};

#endif