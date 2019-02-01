procedure test (p:in) is 
 v : integer;
 c: integer;
 a: integre;
begin 


	v:=1;
	c:=2;
	a:=0;
	loop
	Put(999999999999);
		a := a + 1;
		loop
			Put(11111111111111);
			c:= c+1;
			exit when c=a*10;
		end loop;

		loop
			Put(222222222222222);
			v:= v+1;
			exit when v=2*a*10;
		end loop;

	exit when a=4;
	end loop ;
	Put(c);
	Put(v);
	Put(a);
	
end ;
