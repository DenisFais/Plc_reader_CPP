#include <datatype.hpp>

enum class tipatypes
{
    {"bool",   {  0, 1}},  
    {"byte",   {  1, 0}}, 
    {"char",   {  1, 0}},
    {"word",   {  2, 0}}, 
    {"int",    {  2, 0}},
    {"dint",   {  4, 0}}, 
    {"real",   {  4, 0}},
    {"string", {256, 0}},
    {"date",   {  2, 0}},
    {"dword",  {  4, 0}},
    {"lreal",  {  8, 0}},
    {"sint",   {  1, 0}},
    {"time",   {  4, 0}},
    {"udint",  {  4, 0}},
    {"uint",  {  2, 0}},
    {"usint",  {  1, 0}},
    {"date_and_time",  {  8, 0}}
};