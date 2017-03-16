select * from (select A,B from
(select A,B,c from
(select a,b,c,d from t1)
y3) y2) y1;
insert into t1 values('string',1);
