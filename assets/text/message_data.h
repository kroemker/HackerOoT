#include "text/message_data.h"

DEFINE_MESSAGE(0x8001, TEXTBOX_TYPE_BLUE, TEXTBOX_POS_BOTTOM, MSG(/* MISSING */),
               MSG(UNSKIPPABLE ITEM_ICON(ITEM_ARROW_LIGHT) QUICKTEXT_ENABLE
                   "You got a " COLOR(LIGHTBLUE) "Bundle of Magic Arrows" COLOR(
                       DEFAULT) "!" QUICKTEXT_DISABLE "\n"
                                "Cycle through them using " COLOR(LIGHTBLUE) "[R] " COLOR(
                                    DEFAULT) "\n"
                                             "while holding your bow!" BOX_BREAK
                                             "I wonder what that purple one can do!"),
               MSG(/* MISSING */), MSG(/* MISSING */))

/*
 * The following two messages should be kept last and in this order.
 * Message 0xFFFD must be last to not break the message debugger (see R_MESSAGE_DEBUGGER_TEXTID).
 * Message 0xFFFC must be immediately before message 0xFFFD to not break Font_LoadOrderedFont.
 */
DEFINE_MESSAGE_FFFC(0xFFFC, TEXTBOX_TYPE_BLACK, TEXTBOX_POS_VARIABLE,
                    MSG("０１２３４５６７８９あいうえおかきくけこ\n"
                        "さしすせそたちつてとなにぬねのはひふへほ\n"
                        "まみむめもやゆよらりるれろわをんぁぃぅぇ\n"
                        "ぉっゃゅょがぎぐげござじずぜぞだぢづでど\n"
                        "ばびぶべぼぱぴぷぺぽアイウエオカキクケコ\n"
                        "サシスセソタチツテトナニヌネノハヒフヘホ\n"
                        "マミムメモヤユヨラリルレロワヲンァィゥェ\n"
                        "ォッャュョガギグゲゴザジズゼゾダヂヅデド\n"
                        "バビブベボパピプペポヴＡＢＣＤＥＦＧＨＩ\n"
                        "ＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺａｂｃ\n"
                        "ｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗ\n"
                        "ｘｙｚ　┯？！：−（）゛゜，．／"),
                    MSG("0123456789\n"
                        "ABCDEFGHIJKLMN\n"
                        "OPQRSTUVWXYZ\n"
                        "abcdefghijklmn\n"
                        "opqrstuvwxyz\n"
                        " -.\n"),
                    MSG(/* UNUSED */), MSG(/* UNUSED */))
DEFINE_MESSAGE(0xFFFD, TEXTBOX_TYPE_BLACK, TEXTBOX_POS_VARIABLE, MSG(), MSG(), MSG(), MSG())
