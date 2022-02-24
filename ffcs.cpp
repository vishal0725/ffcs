//This code is for a single day
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool search_theory_slot(string *table, string slot, int &location, bool *occupied)
{
    for (int i=11; i>=0; i--)
    {
        if (table[i]==slot && !occupied[i])
        {
            location=i;
            return true;
        }
    }
    return false;
}

bool search_lab_slot(string *table, string slot1, string slot2, int &location, bool *occupied)
{
    for (int i=10; i>=0; i--)
    {
        if (!occupied[i] && !occupied[i+1] && table[i]==slot1 && table[i+1]==slot2)
        {
            location=i;
            return true;
        }
    }
    return false;
}

void place_slot(string *courses, string *table, int location, bool *occupied, int index, int limit)
{
    if (index>=0 && index<limit)
    {
        table[location]=courses[index];
        occupied[location]=true;
    }
    else
    {
        table[location]=courses[index];
        table[location+1]=courses[index];
        occupied[location]=true;
        occupied[location+1]=true;
    }
}

void unplace_slot(string *table, int location, bool *occupied, int index, int limit)
{
    
    if (index>=0 && index<limit)
    {
        table[location]=(location+65);
        table[location]+='1';
    }
    else
    {
        table[location]=((location-5)+65);
        table[location]+='2';
        table[location+1]=((location-4)+65);
        table[location+1]+='2';
    }
}

bool set_schedule(string *table, string *courses, vector<vector<string>> sub_slots, bool *occupied, int index)
{
    if (index==sub_slots.size())
        return true;
    
    int limit;
    if (sub_slots.size()%2==0)
        limit=sub_slots.size()/2;
    else
        limit=sub_slots.size()/2+1;
    if (index>=0 && index<limit) // for theory courses
    {
        for (int i=sub_slots[index].size()-1; i>=0; i--)
        {
            string slot=sub_slots[index][i];
            int location;
            if (!search_theory_slot(table, slot, location, occupied))
                continue;
            place_slot(courses, table, location, occupied, index, limit);
            if (set_schedule(table, courses, sub_slots, occupied,index+1))
                return true;
            unplace_slot(table, location, occupied, index, limit);
        }
    }
    else // for lab courses
    {
        for (int i=sub_slots[index].size()-1; i>=0; i--)
        {
            string slot1=sub_slots[index][i].substr(0, 2);
            string slot2=sub_slots[index][i].substr(3);
            int location;
            if (!search_lab_slot(table, slot1, slot2, location, occupied))
                continue;
            place_slot(courses, table, location, occupied, index, limit);
            if (set_schedule(table, courses, sub_slots, occupied,index+1))
                return true;
            unplace_slot(table, location, occupied, index, limit);
        }
    }
    return false;
}

void print_schedule(string *table)
{
    for (int i=0; i<12; i++)
        cout << table[i] << '\t';
    cout << endl;
}

int main() 
{
    string table[12];
    for (int i=0; i<6; i++)
    {
        table[i]=(i+65);
        table[i]+='1';
        
        table[6+i]=(i+65);
        table[6+i]+='2';
    }
    
    string courses[10]={"BECEL", "BCSEL", "BPHYL", "BECEP", "BCSEP"};
    
    vector<vector<string>> sub_slots;
    
    //sub_slots.push_back({"A1", "B1", "D1", "A2", "C2"});
    sub_slots.push_back({"A1", "E1", "C2", "E2"});
    sub_slots.push_back({"B1", "D1", "E1", "C2", "E2"});
    sub_slots.push_back({"B1", "C1", "D1", "A2", "B2", "D2"});
    
    //sub_slots.push_back({"A1 B1", "D1 E1", "A2 B2"});
    sub_slots.push_back({"A1 B1", "B1 C1", "D1 E1", "B2 C2"});
    sub_slots.push_back({"A1 B1", "C1 D1", "A2 B2", "B2 C2", "D2 E2"});
    //sub_slots.push_back({"B1 C1", "C1 D1", "B2 C2", "E2 F2"});
    
    bool occupied[12];
    for (int i=0; i<12; i++)
        occupied[i]=false;
    
    cout << "Slots:\n";
    print_schedule(table);
    set_schedule(table, courses, sub_slots, occupied, 0);
    cout << "\nCreated schedule such that student wakes up the latest:\n";
    print_schedule(table);
}
