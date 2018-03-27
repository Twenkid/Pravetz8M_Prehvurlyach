===========================================
опеубзпкъв-8л, бепяхъ 1.1 (ЙЮРН Б 1.0)
===========================================
оПНЦПЮЛЮРЮ МЮ BASIC ГЮ оПЮБЕЖ-82/8л
===========================================
4 IF PEEK (769) <> 169 THEN GOSUB 1200
10 GOSUB 2000
11 GET A$
25 GOSUB 1500
30 INPUT "вереме мнлеп (1-9, 0 - йпюи) ";NN
31 IF NN = 0 THEN END
35 TP = (NN-1) * 4
150 FOR J = 1 TO 30
160 IF TP > 31 THEN GOSUB 700
165 IF TP < 31 THEN GOSUB 500
220 NEXT
240 END
500 REM *вереме*
515 F = 32
519 REM *мскхпюме*
520 POKE 797,0
525 PRINT "вереме "NN
550 FOR P = TP TO TP + 3
560 FOR S = 0 TO 15
570 POKE 798,F
572 POKE 793,P: POKE 794,S
580 CALL 769
582 F = F + 1
587 PRINT "озревйю "P," яейрнп"S
590 NEXT: NEXT
600 POKE 60,0: POKE 61, 32: REM A1L, 1H
605 POKE 62,255: POKE 63,95
610 ?"0 - йпюи, дпсц йкюбхь - опедюбю"
612 GET A$
619 IF A$ = "0" THEN END
620 NN = NN + 1
627 PRINT "опедюбюме!"
630 CALL - 307
640 TP = TP + 4
650 RETURN
700 REM * 3 озревйх 32-34 *
715 F = 32
720 POKE 797,0
725 VTAB 15: PRINT "вереме 9"
750 FOR P = 32 TO 34
760 FOR S = 0 TO 15
770 POKE 798, F
772 POKE 793, P: POKE 794,S
780 CALL 769
782 F = F + 1
785 VTAB 15: HTAB 1
787 PRINT "озрвейю "P"        яейрнп "S
790 NEXT: NEXT
795 PRINT "мюрхямх йкюбхь..."
797 GET A$
800 POKE 60,0: POKE 61,32
805 POKE 62,255: POKE 63,79
810 CALL - 307
815 PRINT "опеубзпкъмерн е нязыеярбемн!"
817 END
820 RETURN
1200 REM * вереме мю яейрнп мю дхяйерюрю *
1220 FOR M = 0 TO 29: READ RR: POKE 769 + M, RR: NEXT
1223 DATA 169,3,160,9,32,217,3,96,0,1,96,1,0,17
1224 DATA 15,26,3,196,134,0,0,1,0,0,96,1,0,1,239,216
1225 RETURN
2000 TEXT: HOME: PRINT "рнь: опеубзпкъв-8л. бепяхъ 1.1"
2005 PRINT "HTTP://TOSH.DATA.BG"
2010 PRINT "HTTP://EIM.HIT.BG"
2010 PRINT "HTTP://WWW.GEOCITIES.COM/TODPROG
2020 PRINT
2200 RETURN