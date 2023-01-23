/*
* SPDX-License-Identifier: GPL-2.0-only
* Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
*/

#ifndef __FSM_IPC_LOGGING_H__
#define __FSM_IPC_LOGGING_H__

#define FSM_DEFAULT_IPC_LOG_PAGES 10

#if defined(CONFIG_IPC_LOGGING)
#include <linux/ipc_logging.h>
#include <linux/string.h>

#define MAX_IPC_LOG_NAME_LEN 25

#define FSM_IPC_LOG_DEBUG(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_debug("[%s]: "__msg, __func__, ##__VA_ARGS__); \
	if (fsm_ipc_log_ctxt) \
		ipc_log_string(fsm_ipc_log_ctxt, \
			"[D][%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)

#define FSM_IPC_LOG_INFO(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_info("[%s]: "__msg, __func__, ##__VA_ARGS__); \
	if (fsm_ipc_log_ctxt) \
		ipc_log_string(fsm_ipc_log_ctxt, \
			"[I][%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)

#define FSM_IPC_LOG_ERROR(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_err("[%s]: "__msg, __func__, ##__VA_ARGS__); \
	if (fsm_ipc_log_ctxt) \
		ipc_log_string(fsm_ipc_log_ctxt, \
			"[E][%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)

#define FSM_IPC_LOG_WARN(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_warn("[%s]: "__msg, __func__, ##__VA_ARGS__); \
	if (fsm_ipc_log_ctxt) \
		ipc_log_string(fsm_ipc_log_ctxt, \
			"[W][%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)


/*
 * fsm_enable_ipc_logging: Wrapper to ipc_log_context_create()
 *
 * @fsm_ipc_log_ctxt_ptr: Pointer to IPC log context
 * @max_num_pages: Number of pages of logging space required
 * @mod_name     : Name of the directory entry under DEBUGFS
 *
 */
static inline void fsm_enable_ipc_logging(
	void **fsm_ipc_log_ctxt_ptr,
	int max_num_pages, const char *modname)
{
	char ipc_log_name[MAX_IPC_LOG_NAME_LEN];
	strlcpy(ipc_log_name, modname, MAX_IPC_LOG_NAME_LEN);
	*fsm_ipc_log_ctxt_ptr = ipc_log_context_create(
		max_num_pages,
		ipc_log_name, 0);
	if (*fsm_ipc_log_ctxt_ptr == NULL)
		pr_err("%s: unable to create IPC log context for %s\n",
			__func__, ipc_log_name);
	else
		FSM_IPC_LOG_DEBUG(*fsm_ipc_log_ctxt_ptr,
			"IPC logging: %s is enabled", ipc_log_name);
}

/*
 * fsm_disable_ipc_logging: Wrapper to ipc_log_context_destroy()
 *
 * @fsm_ipc_log_ctxt_ptr: Pointer to IPC log context
 */
static inline void fsm_disable_ipc_logging(void **fsm_ipc_log_ctxt_ptr)
{
	if (*fsm_ipc_log_ctxt_ptr) {
		ipc_log_context_destroy(*fsm_ipc_log_ctxt_ptr);
		*fsm_ipc_log_ctxt_ptr = NULL;
	}
}

#else

#define FSM_IPC_LOG_DEBUG(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_debug("[%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)

#define FSM_IPC_LOG_INFO(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_info("[%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)

#define FSM_IPC_LOG_ERROR(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_err("[%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)

#define FSM_IPC_LOG_WARN(fsm_ipc_log_ctxt, __msg, ...) \
do { \
	pr_warn("[%s]: "__msg, __func__, ##__VA_ARGS__); \
} while (0)

static inline void fsm_enable_ipc_logging(
	void **fsm_ipc_log_ctxt_ptr,
	int max_num_pages, const char *modname)
{
	*fsm_ipc_log_ctxt_ptr = NULL;
}

static inline void fsm_disable_ipc_logging(void **fsm_ipc_log_ctxt_ptr)
{
	*fsm_ipc_log_ctxt_ptr = NULL;
}
#endif /* CONFIG_IPC_LOGGING */
#endif /* __FSM_IPC_LOGGING_H__ */
