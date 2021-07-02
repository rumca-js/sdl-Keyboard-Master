

DrawComplex::DrawComplex()
{
}

DrawComplex::update(msec)
{
    foreach(item in items)
    {
        item->update(msec);
    }
}
