SQLite format 3   @     	                                                              	 -�#   � zA�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  C_indexFilenameBrowseCREATE INDEX Filename ON Browse(Filename)4KindexTagBrowseCREATE INDEX Tag ON Browse(Tag)7OindexNameBrowseCREATE INDEX Name ON Browse(Name)��atableBrowseBrowseCREATE TABLE Browse (Kind INTEGER,Name TEXT,Tag TEXT,Filename TEXT,Lineno INTEGER,Text TEXT,Extra INTEGER)   �    ����������X4  � � � _ 2+!5logiclogic.c �struct Logic *logic;G 	!eLogic_initlogic.c �struct Logic *Logic_init(int row, int col) {collogic.c �int col)rowlogic.c �int row,memsetlogic.c �assertlogic.c �calloclogic.c �"#cellslogic.c �int *cells;<	QCells_newlogic.c �int *Cells_new(int row, int col) {collogic.c �int col)rowlogic.c �int row,randlogic.c �assertlogic.c �malloclogic.c �+5blocklogic.c �struct Block *block;N	uBlock_newlogic.c �struct Block *Block_new(const struct Logic *logic) {1Alogiclogic.c �const struct Logic *logic)V%Block_Matrixlogic.cconst int Block_Matrix[NBLOCK][NPOS][NMATRIX][NMATRIX] = 
M_CENTERlogic.c:	%'=init_consoleconsole_win.cint init_console(void) {		'�OWinMainconsole_win.cint WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,    �   �   i   S   :   !   �    ���� ��� ��"�c��8�N����$gny��H_z?. �n
�.C�t����	�.�q��{X�g`�� ���P� � �?Z�T�                Block_new[freeZput_blockYtXtempW!Block_moveV'Logic_advanceUdirT	logicS%does_collideR%does_collideQ%does_collideP!Block_moveOdirN	blockM	logicLmemmoveKlinecountJlast_lineI
nlinesHjGiF#clear_linesE	logicD
assertC
is_outBbAy@x?my>mx=i<j;put_block:	block9	logic8
assert7
is_out6b5y4x3my2mx1i0j/%does_collide.	block-	logic,Block_new+Block_new*
assert)Cells_new(
memset'
assert&
malloc%	srand#	block"	logic!!Logic_init WinMain%init_consoletime$colrow
memset
assert
calloc	cellsCells_newcolrowrand
assert
malloc	blockBlock_new	logic%Block   %does_collideP   �    ����������������������zupkfa\WRMHC>94/*% ��������������������������{vqlgb]XSNID?:50+&!���wrm^O@1"�������|        
Block �
Block � �Block_pos �Block_pos �Block_pos �Block_pos �Block_pos �~}!Block_type|!Block_type{!Block_typez!Block_typey!Block_typex!Block_typew!Block_typev!Block_typeutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!       U   �    �������|pdXL@4(�����������th\PD8, �����������xl`TH<0$  � � � � � � � �          logic.cSlogic.cRlogic.cQlogic.cPlogic.cOlogic.cNlogic.cMlogic.cLlogic.cKlogic.cJlogic.cIlogic.cHlogic.cGlogic.cFlogic.cElogic.cDlogic.cClogic.cBlogic.cAlogic.c@logic.c?logic.c>logic.c=logic.c<logic.c;logic.c:logic.c9logic.c8logic.c7logic.c6logic.c5logic.c4logic.c3logic.c2logic.c1logic.c0logic.c/logic.c.logic.c-logic.c,logic.c+logic.c*logic.c)logic.c(logic.c'logic.c&logic.c%logic.c$logic.c#logic.c"logic.c!logic.c logic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.c'   
logic.cq   	logic.c:C  2 (��M ����X4  � � � _ 2 2 2+!5logiclogic.c �struct Logic *logic;G 	!eLogic_initlogic.c �struct Logic *Logic_init(int row, int col) {collogic.c �int col)rowlogic.c �int row,memsetlogic.c �assertlogic.c �calloclogic.c �"#cellslogic.c �int *cells;<	QCells_newlogic.c �int *Cells_new(int row, int col) {collogic.c �int col)rowlogic.c �int row,randlogic.c �assertlogic.c �malloclogic.c �+5blocklogic.c �struct Block *block;N	uBlock_newlogic.c �struct Block *Block_new(const struct Logic *logic) {1Alogiclogic.c �const struct Logic *logic)V%Block_Matrixlogic.cconst int Block_Matrix[NBLOCK][NPOS][NMATRIX][NMATRIX] = 
M_CENTERlogic.c   �%'=init_consoleconsole_win.cint init_console(void) {   �'�OWinMainconsole_win.cint WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {    I ����nT7 ��}�����dG  � � I               [:		�put_blocklogic.c#void put_block(struct Logic *logic, const struct Block *block) {19Ablocklogic.c#const struct Block *block)+85logiclogic.c#struct Logic *logic,7assertlogic.c%6'is_outlogic.cint is_out = 5blogic.cint b = 4ylogic.cint y = 3xlogic.cint x = 2mylogic.cint my = 1mxlogic.cint mx = 0ilogic.cint j, i;/jlogic.cint j,f.		%�does_collidelogic.c	int does_collide(const struct Logic *logic, const struct Block *block) {1-Ablocklogic.c	const struct Block *block)1,Alogiclogic.c	const struct Logic *logic,+Block_newlogic.c *Block_newlogic.c �)assertlogic.c �(Cells_newlogic.c �'memsetlogic.c �&assertlogic.c �%malloclogic.c �$timelogic.c �#srandlogic.c �+"5blocklogic.c �struct Block *block;    F ����lO2���gI"����S4 � � � s F         3+S5logiclogic.cstruct Logic *logic,R%does_collidelogic.crQ%does_collidelogic.ckP%does_collidelogic.cd_O		!�Block_movelogic.c_int Block_move(struct Logic *logic, struct Block *block, int dir) {Ndirlogic.c_int dir)+M5blocklogic.c_struct Block *block,+L5logiclogic.c_struct Logic *logic,Kmemmovelogic.cR+J-linecountlogic.cEint linecount = +I-last_linelogic.cBint last_line = %H'nlineslogic.cAint nlines = Gjlogic.c@int i, j;Filogic.c@int i,BE	#Yclear_lineslogic.c>int clear_lines(struct Logic *logic) {+D5logiclogic.c>struct Logic *logic)Cassertlogic.c4#B#is_outlogic.c.int is_out;Ablogic.c-int b = @ylogic.c,int y = ?xlogic.c+int x = >mylogic.c'int my = =mxlogic.c&int mx = <ilogic.c%int j, i;;jlogic.c%int j,
   9 � dw������Q>+ �� ,8DP\ht�����������(4@LXdp|����������p|����������'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �'console_win.c �logic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.clogic.c logic.c!logic.c"logic.c#logic.c$logic.c%logic.c&logic.c'logic.c(logic.c)logic.c*logic.c+logic.c,logic.c-logic.c.logic.c/logic.c0logic.c1logic.c2logic.c3logic.c4logic.c5logic.c6logic.c7logic.c8logic.c9
   6x x����������� ,8DP\ht�����������(4@LXdp|����������#0=JWdq~��������� logic.cNlogic.cOlogic.cPlogic.cQlogic.cRlogic.cSlogic.cTlogic.cUlogic.cVlogic.cWlogic.cXlogic.cYlogic.cZlogic.c[logic.c\logic.c]logic.c^logic.c_logiclogic.c;logic.c<logic.c=logic.c>logic.c?logic.c@logic.cAlogic.cBlogic.cClogic.cDlogic.cElogic.cFlogic.cGlogic.cHlogic.cIlogic.cJlogic.cKlogic.cLlogic.cMlogic.cNlogic.cOlogic.cPlogic.cQlogic.cRlogic.cSlogic.cTlogic.cUlogic.cVlogic.cWlogic.cXlogic.cYlogic.cZlogic.c[logic.c\logic.c]logic.c^logic.c_logic.c`logic.calogic.cblogic.cclogic.cdlogic.celogic.cflogic.cglogic.chlogic.cilogic.cjlogic.cklogic.cllogic.cmlogic.cnlogic.cologic.cp    b ��rG,����hD���pV9 � � b                                              i%does_collidelogic.c�[h		%�Block_rotatelogic.c�void Block_rotate(struct Logic *logic, struct Block *block) {+g5blocklogic.c�struct Block *block)+f5logiclogic.c�struct Logic *logic,eput_blocklogic.c�dmemcpylogic.c�cmemcpylogic.c�,b5tlogiclogic.c�struct Logic tlogic;,a7blocklogic.c�struct Block *block =\`		)�Logic_get_celllogic.c�void Logic_get_cell(const struct Logic *logic, int *cells) {"_#cellslogic.c�int *cells)1^Alogiclogic.c�const struct Logic *logic,]#clear_lineslogic.c�\%does_collidelogic.c�[Block_newlogic.c�Zfreelogic.c�Yput_blocklogic.c�Xtlogic.c�int t;)W3templogic.c�struct Block *temp;V!Block_movelogic.c�OU	'oLogic_advancelogic.cint Logic_advance(struct Logic *logic, int dir) {Tdirlogic.cint dir)
   F �  � � � � � �)7ESbs�����������$3BO_jv������������$*0:DNXblv����������� � WinMain �%d%AllocConsole �
Block �%Block_Matrix%Block_Matrix �+Block_hard_dropk!Block_moveO!Block_moveVBlock_newBlock_new*Block_new+Block_new[Block_pos �%Block_rotateh!Block_typeuCells_newCells_new(	DOWN �%GetStdHandle �%GetStdHandle �I{Lx	LEFT �
Logic �'Logic_advanceU'Logic_advancen)Logic_get_cell`!Logic_init !Logic_quitpM_CENTER!MessageBox �
NBLOCK}NMATRIX~NPOS
RIGHT �RLyRZ|Sz+SetConsoleTitle �TvUP �WinMain �Zw__LOGIC_Ht
assert
assert
assert&
assert)
assert7
assertCb5bA	block	block"	block-	block9	blockM	blocka	blockg
calloc	cells	cells_
cells �#clear_linesE#clear_lines]colcolcur_block �dirNdirT%does_collide.
   M �  � � �&/8GZev�������������!,6@JT^hr|������������!+;FPYgu����������������                                              %does_collideQ%does_collideR%does_collide\%does_collideifreeZfreeqfreerfreeshInstance �'hPrevInstance �
heightl#hndConInput �%hndConOutput �i0i<iFid �%init_console �%init_console �isOver �
is_out6
is_outBj/j;jGlast_lineI
level �linecountJ
lines �	logic	logic!	logic,	logic8	logicD	logicL	logicS	logic^	logicf	logicj	logicolpCmdLine �
malloc
malloc%
memcpyc
memcpydmemmoveK
memset
memset'mx1mx=my2my>nShowCmd �	ncol �!next_block �
nlinesH	nrow �pos �put_block:put_blockYput_blockerandrowrow
score �	srand#tXtmtempWtime$
tlogicbx3x?x �y4y@y �    H ��_D#����kO(
����sT;!
 � � � � a H        �Blocklogic.h	�	DOWNBlock_poslogic.h�	RIGHTBlock_poslogic.h�	LEFTBlock_poslogic.h�	UPBlock_poslogic.h#� Block_posBlock_poslogic.h	NPOSlogic.h~	NMATRIXlogic.h}	NBLOCKlogic.h|!	RZBlock_typelogic.h{!	IBlock_typelogic.hz!	SBlock_typelogic.hy!	RLBlock_typelogic.hx!	LBlock_typelogic.hw!	ZBlock_typelogic.hv!	TBlock_typelogic.h%u!!Block_typeBlock_typelogic.ht
__LOGIC_Hlogic.hsfreelogic.c�rfreelogic.c�qfreelogic.c�Ap	!YLogic_quitlogic.c�void Logic_quit(struct Logic *logic) {+o5logiclogic.c�struct Logic *logic)n'Logic_advancelogic.c�mtlogic.c�int t;%l'heightlogic.c�int height = Kk	+cBlock_hard_droplogic.c�void Block_hard_drop(struct Logic *logic) {+j5logiclogic.c�struct Logic *logic)    L ���w^5��sK#��zB � � � r L                          #�%'GetStdHandleconsole_win.c
#�%'GetStdHandleconsole_win.c	#�%'AllocConsoleconsole_win.c:�	%'=init_consoleconsole_win.cint init_console(void) {D�%'OhndConOutputconsole_win.cHANDLE hndConInput, hndConOutput;5�#'3hndConInputconsole_win.cHANDLE hndConInput,T�%{Block_Matrixlogic.hconst int Block_Matrix[NBLOCK][NPOS][NMATRIX][NMATRIX];'�#isOverLogiclogic.hint isOver;%�!linesLogiclogic.hint lines;%�!scoreLogiclogic.hint score;%�!levelLogiclogic.hint level;9�!?next_blockLogiclogic.hstruct Block *next_block;7�=cur_blockLogiclogic.hstruct Block *cur_block;#�ncolLogiclogic.hint ncol;#�nrowLogiclogic.hint nrow;&�#cellsLogiclogic.hint *cells;�
Logiclogic.h �	yBlocklogic.hint x, y;�xBlocklogic.hint x,!�posBlocklogic.hint pos;�idBlocklogic.h
int id;
   F� �������������������$).38=BGLQV[`ejoty~�������������������������������{vqlgb]XSNID?:50+&!���wrm^O@1"�������|        
Block �
Block � �Block_pos �Block_pos �Block_pos �Block_pos �Block_pos �~}!Block_type|!Block_type{!Block_typez!Block_typey!Block_typex!Block_typew!Block_typev!Block_typeutsrqponmlkjihgfedcba`_^]\[ZYXWVU       !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST
   M� lqv{��������������������������[���������������'2a=L[jy��������PE:/$�                                                                                                                                                                                                                                                         {p � � � � � � � � � � � � � � �
Logic �
Logic �
Logic �
Logic �
Logic �
Logic �
Logic �
Logic �
Logic � �
Block �VWXYZ[\]^_`abcdefghijklmnopqrst}~ �
Block �
Block �
Block �Block_pos �Block_pos �Block_pos �Block_pos �Block_pos �!Block_typeu!Block_typev!Block_typew!Block_typex!Block_typey!Block_typez!Block_type{!Block_type|   3 ��a.�}W3                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           !�"!'MessageBoxconsole_win.c#�!%'init_consoleconsole_win.c� 		'�OWinMainconsole_win.cint WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {,�''nShowCmdconsole_win.cint nShowCmd)0�'-lpCmdLineconsole_win.cLPSTR lpCmdLine,<�''=hPrevInstanceconsole_win.cHINSTANCE hPrevInstance,4�'5hInstanceconsole_win.cHINSTANCE hInstance,&�+'SetConsoleTitleconsole_win.c
   #G GS_kw�����������	#0=JWdq~���������                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         logic.crlogic.cslogic.htlogic.hulogic.hvlogic.hwlogic.hxlogic.hylogic.hzlogic.h{logic.h|logic.h}logic.h~logic.hlogic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �logic.h �