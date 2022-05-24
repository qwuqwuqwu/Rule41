#include <iostream>
using namespace std;

int g_someNastyWidget = 10;
// REF: https://stackoverflow.com/questions/51961555/effective-c-item-41-confusion-about-implicit-interfaces
// for ">"
struct Z {
    int nData;

    Z( int n )
    {
        nData = n;
    }

    bool operator> ( int nOther )
    {
        return ( nData > nOther );
    }
};

// ========================================================
class Widget {
public:
    Widget( int nVal ) : m_nVal( nVal ) {}
    virtual ~Widget() {}
    //virtual std::size_t size() const { return 0; }
    virtual Z size() const { return Z( m_nVal ); } // size() do not return int
    virtual void normalize() { m_nVal /= 2; }
    void swap( Widget& other )
    {
        int nVal = m_nVal;
        m_nVal = other.m_nVal;
        other.m_nVal = nVal;
    }

public:
    int GetVal( void ) { return m_nVal; }
    friend ostream &operator<<( ostream &s, Widget w )
    {
        cout << "Widget val is " << w.GetVal() << endl;
        return s;
    }

private:
    int m_nVal;
};

// ========================================================

class Y {
public:
    Y( int n ):m_n( n ){};
    int m_n;
};

class X {
public:
    X( const Widget& W ) {};
};

// X(w) != g_someNastyWidget
bool operator!=( const X& x, const Y& y )
{
    return true;
}

template< typename T >
void doProcessing( T& w )
{
    if( w.size() > 10 && w != g_someNastyWidget ) {
        T temp( w );
        temp.normalize();
        temp.swap( w );
    }
}

int main( void )
{
    Widget MyWidget( 11 );
    cout << MyWidget;

    doProcessing( MyWidget );
    cout << MyWidget;
    return 0;
}