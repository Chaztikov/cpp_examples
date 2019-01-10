template <class T>
class point    // note: private inheritance is OK here!
    : boost::addable< point<T>          // point + point
    , boost::subtractable< point<T>     // point - point
    , boost::dividable2< point<T>, T    // point / T
    , boost::multipliable2< point<T>, T // point * T, T * point
      > > > >
{
public:
    point(T, T);
    T x() const;
    T y() const;

    point operator+=(const point&);
    // point operator+(point, const point&) automatically
    // generated by addable.

    point operator-=(const point&);
    // point operator-(point, const point&) automatically
    // generated by subtractable.

    point operator*=(T);
    // point operator*(point, const T&) and
    // point operator*(const T&, point) auto-generated
    // by multipliable.

    point operator/=(T);
    // point operator/(point, const T&) auto-generated
    // by dividable.
private:
    T x_;
    T y_;
};

// now use the point<> class:

template <class T>
T length(const point<T> p)
{
    return sqrt(p.x()*p.x() + p.y()*p.y());
}

const point<float> right(0, 1);
const point<float> up(1, 0);
const point<float> pi_over_4 = up + right;
const point<float> pi_over_4_normalized = pi_over_4 / length(pi_over_4);