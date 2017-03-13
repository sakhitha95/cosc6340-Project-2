select * from (select A,B from (select A,B,c from (select a,b,c,d from t1) y3) y2) y1;
