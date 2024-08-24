#ifndef INTERFACE_H
#define INTERFACE_H

#pragma once

namespace Interface
{
    class Pointable
    {
    public:
        virtual bool pointed(int x, int y) = 0;
    };
    
    // class Drawn
    // {
    // public:
    //     virtual void draw() const = 0;
    // };
};

#endif