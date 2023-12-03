#ifndef OCEANBASE_SHARE_OB_CREATE_TABLE_TH_H
#define OCEANBASE_SHARE_OB_CREATE_TABLE_TH_H

#include "lib/ob_define.h"
#include "lib/lock/ob_futex.h"
#include "lib/thread/ob_thread_name.h"
#include "lib/thread/thread_mgr_interface.h"
#include "rpc/frame/ob_net_easy.h"
#include "observer/ob_srv_network_frame.h"
#include <functional>

namespace oceanbase {
namespace share {

class ObCreateTableTh: public lib::TGRunnable
{
public:
  ObCreateTableTh();
  virtual ~ObCreateTableTh();
  int init(std::function<void()>&);
  void destroy();
  int start();
  int stop();
  int wait();
  virtual void run1();

private:

  bool is_inited_ = false;
  int tg_id_;
  std::function<void()> func_;
};
} // namespace share
} // namespace oceanbase

#endif