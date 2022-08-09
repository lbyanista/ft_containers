#pragma once

template<class T1, class T2>
        struct pair {
            typedef first_type;
            typedef second_type;

            T1 first;
            T2 second;
            pair(){}
            pair(const T1 &x, const T2 &y);
            template<class U, class V>
                pair(const pair<U, V> &p);
        };
        // pair();