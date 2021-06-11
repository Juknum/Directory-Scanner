BASENAME(1)                      User Commands                     BASENAME(1)

NNAAMMEE
       basename - strip directory and suffix from filenames

SSYYNNOOPPSSIISS
       bbaasseennaammee _N_A_M_E [_S_U_F_F_I_X]
       bbaasseennaammee _O_P_T_I_O_N... _N_A_M_E...

DDEESSCCRRIIPPTTIIOONN
       Print  NAME  with  any leading directory components removed.  If speci‐
       fied, also remove a trailing SUFFIX.

       Mandatory arguments to long options are  mandatory  for  short  options
       too.

       --aa, ----mmuullttiippllee
              support multiple arguments and treat each as a NAME

       --ss, ----ssuuffffiixx=_S_U_F_F_I_X
              remove a trailing SUFFIX; implies --aa

       --zz, ----zzeerroo
              end each output line with NUL, not newline

       ----hheellpp display this help and exit

       ----vveerrssiioonn
              output version information and exit

EEXXAAMMPPLLEESS
       basename /usr/bin/sort
              -> "sort"

       basename include/stdio.h .h
              -> "stdio"

       basename -s .h include/stdio.h
              -> "stdio"

       basename -a any/str1 any/str2
              -> "str1" followed by "str2"

AAUUTTHHOORR
       Written by David MacKenzie.

RREEPPOORRTTIINNGG BBUUGGSS
       GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
       Report    basename   translation   bugs   to   <https://translationpro‐
       ject.org/team/>

CCOOPPYYRRIIGGHHTT
       Copyright © 2018 Free Software Foundation, Inc.   License  GPLv3+:  GNU
       GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
       This  is  free  software:  you  are free to change and redistribute it.
       There is NO WARRANTY, to the extent permitted by law.

SSEEEE AALLSSOO
       dirname(1), readlink(1)

       Full  documentation  at:  <https://www.gnu.org/software/coreutils/base‐
       name>
       or available locally via: info '(coreutils) basename invocation'

GNU coreutils 8.30              September 2019                     BASENAME(1)
