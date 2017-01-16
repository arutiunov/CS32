class Creature
{
public:
    Creature(string name);
    virtual ~Creature();
    virtual string move() const = 0;
    string name() const;
    virtual bool isMortal() const;
private:
    string m_name;
};

Creature::Creature(string name)
        :m_name(name)
{}

Creature::~Creature()
{}

string Creature::name() const
{
    return m_name;
}

bool Creature::isMortal() const
{
    return true;
}


class Phoenix : public Creature
{
public:
    Phoenix(string name);
    ~Phoenix();
    string move() const;
    bool isMortal() const; 
private:
    string m_move;
};

Phoenix::Phoenix(string name)
:Creature(name), m_move("fly")
{}

Phoenix::~Phoenix()
{
    cout << "Destroying " << name() << " the phoenix." << endl;
}

string Phoenix::move() const
{
    return m_move;
}

bool Phoenix::isMortal() const
{
    return false;
}

class Giant : public Creature
{
public:
    Giant(string name, int size);
    ~Giant();
    string move() const;
private:
    string m_move1;
    string m_move2;
    int m_size;
};

Giant::Giant(string name, int size)
: Creature(name), m_size(size), m_move1("tromp"), m_move2("lumber")
{}

Giant::~Giant()
{
    cout << "Destroying " << name() << " the giant." << endl;
}

string Giant::move() const
{
    if (m_size < 20)
        return m_move1;
    
    else
        return m_move2;
    
}

class Centaur : public Creature
{
public:
    Centaur(string name);
    ~Centaur();
    string move() const;
private:
    string m_move;
};

Centaur::Centaur(string name)
: Creature(name), m_move("trot")
{}

Centaur::~Centaur()
{
    cout << "Destroying " << name() << " the centaur." << endl;
}

string Centaur::move() const
{
    return m_move;
}