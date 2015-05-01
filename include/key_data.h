#ifndef KEY_DATA_H
#define KEY_DATA_H

// Key for key manager
class key_data
{
  public:
    key_data(int newValue);
    virtual ~key_data();

    // Get key value
    int getValue();
  protected:
  private:
    // Value stored
    int value;
};

#endif // KEY_DATA_H
