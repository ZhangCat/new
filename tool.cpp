

int filesize_c(FILE *fp)
{
	if(fp)
	{
		fseek(fp,0L,SEEK_END);
		int size=ftell(fp);
		fseek(fp,0L,SEEK_SET);
		return size;
	}
	return -1;
}

int filesize_cxx(fstream &fs)
{
	if(fs.good())
	{
		fs.seekg(0,ios::end);
		streampos size=fs.tellg();
		fs.seekg(0,ios::beg);	
		return (int)size;
	}
	return -1;
}