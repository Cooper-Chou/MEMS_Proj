template <typename T>
T modulus(T _origin_num, T _modulus_length)
{
    return (_origin_num % _modulus_length + _modulus_length) % _modulus_length;
}