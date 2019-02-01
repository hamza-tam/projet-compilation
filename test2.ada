procedure test is 
 v : integer;
begin 
	loop
		Get(v);
		exit when v = 1;
	end loop;
	Put(v);
end ;
