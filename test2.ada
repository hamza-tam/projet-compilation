procedure main is

	v:Integer;


	procedure inc is 
		a:Integer;
	begin 
		Get(a);
		Put(a+1);
		Put('\n');
	end;

begin 

	loop 
		Put("Entrez v: ");
		Get(v);

		inc;

		exit when v = 0;
	end loop;

end;