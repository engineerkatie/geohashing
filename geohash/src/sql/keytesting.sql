DROP TABLE hashed;

CREATE TABLE hashed
  ( hash BLOCK PRIMARY KEY
  , name STRING
);

INSERT INTO hashed(hash, name) VALUES(X'00000000000001', 'L0 p0,0');
INSERT INTO hashed(hash, name) VALUES(X'01000000000002', 'L1 p0,0');
INSERT INTO hashed(hash, name) VALUES(X'02000000000003', 'L2 p0,0');

INSERT INTO hashed(hash, name) VALUES(X'00200000000004', 'L0 p1,0');
INSERT INTO hashed(hash, name) VALUES(X'01000000000005', 'L1 p1,0');
INSERT INTO hashed(hash, name) VALUES(X'02000000000006', 'L2 p1,0');

INSERT INTO hashed(hash, name) VALUES(X'00800000000007', 'L0 p2,0');
INSERT INTO hashed(hash, name) VALUES(X'01800000000008', 'L1 p2,0');
INSERT INTO hashed(hash, name) VALUES(X'02800000000009', 'L2 p2,0');

INSERT INTO hashed(hash, name) VALUES(X'00a0000000000A', 'L0 p3,0');
INSERT INTO hashed(hash, name) VALUES(X'0180000000000B', 'L1 p3,0');
INSERT INTO hashed(hash, name) VALUES(X'0280000000000C', 'L2 p3,0');

INSERT INTO hashed(hash, name) VALUES(X'0040000000000D', 'L0 p0,1');
INSERT INTO hashed(hash, name) VALUES(X'0140000000000E', 'L1 p0,1');
INSERT INTO hashed(hash, name) VALUES(X'0200000000000F', 'L2 p0,1');

INSERT INTO hashed(hash, name) VALUES(X'00600000000010', 'L0 p1,1');
INSERT INTO hashed(hash, name) VALUES(X'01400000000011', 'L1 p1,1');
INSERT INTO hashed(hash, name) VALUES(X'02000000000012', 'L2 p1,1');

INSERT INTO hashed(hash, name) VALUES(X'00C00000000013', 'L0 p2,1');
INSERT INTO hashed(hash, name) VALUES(X'01C00000000014', 'L1 p2,1');
INSERT INTO hashed(hash, name) VALUES(X'02800000000015', 'L2 p2,1');

INSERT INTO hashed(hash, name) VALUES(X'00E00000000016', 'L0 p3,1');
INSERT INTO hashed(hash, name) VALUES(X'01C00000000017', 'L1 p3,1');
INSERT INTO hashed(hash, name) VALUES(X'02800000000018', 'L2 p3,1');


SELECT * from hashed WHERE hash > X'0140' and hash < X'0180';
