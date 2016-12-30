bool search(int value, int values[], int n)
{
    //  Return false immediately if n is negative
    if (n < 0)
    {
        return false;
    }
    
    //  For linear search: iterate over all elements in values[] and compare to value.  If match return true
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
        return true;
    }
    
    //  if no match found, return false  
    return false;
}
