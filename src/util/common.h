#ifndef XUI_util_common_h
#define XUI_util_common_h

#define colorUnpack(c) c.r,c.g,c.b,c.a

#define Rect(x, y, w, h) ((SDL_Rect){(x),(y),(w),(h)})
#define inRect(tx, ty, r) (((tx)>=(r).x) && ((tx)<((r).x+(r).w)) && ((ty)>=(r).y) && ((ty)<((r).y+(r).h)))

#define MIN(x, y) ((x) < (y) ? (x) : y)
#define MAX(x, y) ((x) > (y) ? (x) : y)

#endif
