/*********************IMPORTANT DRAKVUF LICENSE TERMS***********************
 *                                                                         *
 * DRAKVUF (C) 2014-2019 Tamas K Lengyel.                                  *
 * Tamas K Lengyel is hereinafter referred to as the author.               *
 * This program is free software; you may redistribute and/or modify it    *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE   *
 * CLARIFICATIONS AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your   *
 * right to use, modify, and redistribute this software under certain      *
 * conditions.  If you wish to embed DRAKVUF technology into proprietary   *
 * software, alternative licenses can be aquired from the author.          *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Reads or includes copyrighted data files.                             *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * DRAKVUF with other software in compressed or archival form does not     *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
 * of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the terms and conditions of this license text as well.        *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * DRAKVUF or grant special permissions to use it in other open source     *
 * software.  Please contact tamas.k.lengyel@gmail.com with any such       *
 * requests.  Similarly, we don't incorporate incompatible open source     *
 * software into Covered Software without special permission from the      *
 * copyright holders.                                                      *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * DRAKVUF in other works, are happy to help.  As mentioned above,         *
 * alternative license can be requested from the author to integrate       *
 * DRAKVUF into proprietary applications and appliances.  Please email     *
 * tamas.k.lengyel@gmail.com for further information.                      *
 *                                                                         *
 * If you have received a written license agreement or contract for        *
 * Covered Software stating terms other than these, you may choose to use  *
 * and redistribute Covered Software under those terms instead of these.   *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes.          *
 *                                                                         *
 * Source code also allows you to port DRAKVUF to new platforms, fix bugs, *
 * and add new features.  You are highly encouraged to submit your changes *
 * on https://github.com/tklengyel/drakvuf, or by other methods.           *
 * By sending these changes, it is understood (unless you specify          *
 * otherwise) that you are offering unlimited, non-exclusive right to      *
 * reuse, modify, and relicense the code.  DRAKVUF will always be          *
 * available Open Source, but this is important because the inability to   *
 * relicense code has caused devastating problems for other Free Software  *
 * projects (such as KDE and NASM).                                        *
 * To specify special license conditions of your contributions, just say   *
 * so when you send them.                                                  *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the DRAKVUF   *
 * license file for more details (it's in a COPYING file included with     *
 * DRAKVUF, and also available from                                        *
 * https://github.com/tklengyel/drakvuf/COPYING)                           *
 *                                                                         *
 ***************************************************************************/

#include <stdarg.h>
#include "plugins.h"
#include "syscalls/syscalls.h"
#include "poolmon/poolmon.h"
#include "filetracer/filetracer.h"
#include "filedelete/filedelete.h"
#include "objmon/objmon.h"
#include "exmon/exmon.h"
#include "ssdtmon/ssdtmon.h"
#include "debugmon/debugmon.h"
#include "delaymon/delaymon.h"
#include "cpuidmon/cpuidmon.h"
#include "socketmon/socketmon.h"
#include "regmon/regmon.h"
#include "procmon/procmon.h"
#include "bsodmon/bsodmon.h"
#include "crashmon/crashmon.h"

drakvuf_plugins::drakvuf_plugins(const drakvuf_t drakvuf, output_format_t output, os_t os)
    : drakvuf{ drakvuf }, output{ output }, os{ os }
{
}

drakvuf_plugins::~drakvuf_plugins()
{
    for (int i=0; i<__DRAKVUF_PLUGIN_LIST_MAX; i++)
        delete plugins[i];
}

int drakvuf_plugins::start(const drakvuf_plugin_t plugin_id,
                           const void* config)
{
    if ( __DRAKVUF_PLUGIN_LIST_MAX != 0 &&
            plugin_id < __DRAKVUF_PLUGIN_LIST_MAX)
    {
        PRINT_DEBUG("Starting plugin %s\n", drakvuf_plugin_names[plugin_id]);

        if ( !drakvuf_plugin_os_support[plugin_id][this->os] )
            return 0;

        try
        {
            switch (plugin_id)
            {
#ifdef ENABLE_PLUGIN_SYSCALLS
                case PLUGIN_SYSCALLS:
                    this->plugins[plugin_id] = new syscalls(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_POOLMON
                case PLUGIN_POOLMON:
                    this->plugins[plugin_id] = new poolmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_FILETRACER
                case PLUGIN_FILETRACER:
                    this->plugins[plugin_id] = new filetracer(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_FILEDELETE
                case PLUGIN_FILEDELETE:
                    this->plugins[plugin_id] = new filedelete(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_OBJMON
                case PLUGIN_OBJMON:
                    this->plugins[plugin_id] = new objmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_EXMON
                case PLUGIN_EXMON:
                    this->plugins[plugin_id] = new exmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_SSDTMON
                case PLUGIN_SSDTMON:
                    this->plugins[plugin_id] = new ssdtmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_DEBUGMON
                case PLUGIN_DEBUGMON:
                    this->plugins[plugin_id] = new debugmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_DELAYMON
                case PLUGIN_DELAYMON:
                    this->plugins[plugin_id] = new delaymon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_CPUIDMON
                case PLUGIN_CPUIDMON:
                    this->plugins[plugin_id] = new cpuidmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_SOCKETMON
                case PLUGIN_SOCKETMON:
                    this->plugins[plugin_id] = new socketmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_REGMON
                case PLUGIN_REGMON:
                    this->plugins[plugin_id] = new regmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_PROCMON
                case PLUGIN_PROCMON:
                    this->plugins[plugin_id] = new procmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_BSODMON
                case PLUGIN_BSODMON:
                    this->plugins[plugin_id] = new bsodmon(this->drakvuf, config, this->output);
                    break;
#endif
#ifdef ENABLE_PLUGIN_CRASHMON
                case PLUGIN_CRASHMON:
                    this->plugins[plugin_id] = new crashmon(this->drakvuf, config, this->output);
                    break;
#endif
                default:
                    break;
            }
        }
        catch (int e)
        {
            fprintf(stderr, "Plugin %s startup failed!\n", drakvuf_plugin_names[plugin_id]);
            return -1;
        }

        PRINT_DEBUG("Starting plugin %s finished\n", drakvuf_plugin_names[plugin_id]);
        return 1;
    }

    return 0;
}
