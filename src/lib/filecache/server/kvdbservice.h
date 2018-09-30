/*
* vzes
* Copyright 2013 - 2018, Vzenith Inc.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*  3. The name of the author may not be used to endorse or promote products
*     derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SRC_LIBVZTINYDB_KVDBSERVICE_H_
#define SRC_LIBVZTINYDB_KVDBSERVICE_H_

#include <string>
#include <stdio.h>
#include <time.h>
#include "eventservice/base/basicincludes.h"

namespace cache {

#define KVDB_FILE_PATH_MAXLEN    128   ///< �ļ�ȫ·�����Ƴ���
#define KVDB_KEY_MAXLEN          64    ///< �ؼ����ַ�������
#define KVDB_CACHE_MAXNUM        4     ///< �������
#define KVDB_CACHE_EACH_MAXCNT   1000  ///< ÿ�ֻ�������ڵ���


#ifdef WIN32
#define MAKE_FILE_NAME(X,N,Y,Z) snprintf(X, N, "%s\\%s", Y, Z)
#else
#define MAKE_FILE_NAME(X,N,Y,Z) snprintf(X, N, "%s/%s", Y, Z)
#endif

/**@name    �������Ͷ���
* @{
*/
typedef int KvdbError;
#define KVDB_ERR_OK              0  ///< ��ȷ
#define KVDB_ERR_OPEN_FILE       1  ///< ���ļ�����
#define KVDB_ERR_WRITE_FILE      2  ///< д�ļ�����
#define KVDB_ERR_READ_FILE       3  ///< ���ļ�����
#define KVDB_ERR_PARSE_FILE      4  ///< �����ļ�����
#define KVDB_ERR_INVALID_PARAM   5  ///< ��Ч��������
#define KVDB_ERR_SEEK_NULL       6  ///< ���ҽ��Ϊ��
#define KVDB_ERR_FULL            7  ///< ���ݿ�������
#define KVDB_ERR_DELETE_FILE     8  ///< �ļ�ɾ������
#define KVDB_ERR_OPEN_FOLD       9  ///< ���ļ��д���
#define KVDB_ERR_UNKNOWN         99 ///< δ֪����
/**@} */

/**@name    ״̬��ʶλ����
* @{
*/
#define KVDB_HEAD_FLAG           0x47  ///< ��ʼ��ʶ
#define KVDB_STATUS_BIT_VALID    0x01  ///< ��Чλ��0=���С�1=��Ч
/**@} */

/**
* KVDB���湹��ṹ�壨������ʣ�
*/
struct KvdbCache {
  int size;        ///< �ڵ��С
  int counter;     ///< �ڵ����
};

/**
* KVDB����ṹ�壨����ʹ�ã�
*/
struct KvdbRecord {
  uint8   status;     ///<  ״̬��ʶ��VZ_TDB_HEAD_BIT_VALID
  time_t  time_last;  ///<  �ϴη���ʱ��
  char    key[KVDB_KEY_MAXLEN + 1];  ///< �ؼ���KEY
  int     length;     ///
  uint8  *value;      ///< �ؼ���VALUE����ͬ��λ��Ӧ��ͬ����
  struct  KvdbRecord *next;  ///< ��һ������
};

class KvdbService {
 public:
  /**
  * @brief ���캯��
  * �����ļ�������skvdb����ͨkvdb��ҵ���ʵ�ֲ�ͬ��������
  * ����������Ҫ���ݳ�����С��������
  * @param[in] foldpath    �ļ���·��
  * @param[in] cache       �������Ͷ�������
  * @param[in] cache_cnt   �������Ͷ������
  */
  KvdbService(const char *foldpath, struct KvdbCache *cache, int cache_cnt);
  /**
  * @brief ��������
  */
  ~KvdbService();
  /**
  * @brief �޸Ļ�����һ����¼
  * ����ѱ�����ͬ�ؼ��ּ�¼���޸ģ���������
  * @param[in] key    �ؼ���
  * @param[in] value    ֵ
  * @param[in] length   ֵ����
  *
  * @return ���ز������
  */
  KvdbError Replace(const std::string &key, const uint8 *value, int length);
  /**
  * @brief �޸Ļ�����һ����¼
  * ����ѱ�����ͬ�ؼ��ּ�¼���޸ģ���������
  * @param[in] key    �ؼ���
  * @param[in] value    ֵ
  *
  * @return ���ز������
  */
  KvdbError Replace(const std::string &key, const std::string &value);
  /**
  * @brief ɾ����¼
  * @param[in] key    �ؼ���
  *
  * @return ���ز������
  */
  KvdbError Remove(const std::string &key);
  /**
  * @brief ��ռ�¼
  * @param[in] target_fold    ����յ��ļ���Ŀ¼
  *
  * @return ���ز������
  */
  KvdbError Clear(const char *target_fold = NULL);
  /**
    * @brief ���Ҽ�¼
    * ���ݹؼ��ֲ��Ҽ�¼
    * @param[in] key     ����ؼ���
    * @param[out] get_value     ��ѯ���
    * @param[inout] length     ���룺�����С�������ʵ�ʶ�ȡ����
    *
    * @return ���ز������
    */
  KvdbError Seek(const std::string &key, uint8 *get_data, int *length);
  /**
  * @brief ���Ҽ�¼
  * ���ݹؼ��ֲ��Ҽ�¼
  * @param[in] key     ����ؼ���
  * @param[out] get_value     ��ѯ���
  *
  * @return ���ز������
  */
  KvdbError Seek(const std::string &key, std::string &get_value);
  /**
  * @brief ����
  *  ����ǰ�ļ����ļ����ݵ������ļ���
  * @param[in] backup_fold    �����ļ���·��
  *
  * @return ���ز������
  */
  KvdbError Backup(const char *backup_fold);
  /**
  * @brief ��ԭ
  *  �������ļ����ļ����ݵ���ǰ�ļ���
  * @param[in] backup_fold    �����ļ���·��
  *
  * @return ���ز������
  */
  KvdbError Restore(const char *backup_fold);

#ifdef _DEBUG
  /**
  * @brief ��ӡ����
  *  ���Դ��룬��ӡ��������Ч�ڵ���Ϣ
  */
  void DebugCacheShow();
#endif

 private:
  /**
  * @brief �����ļ���
  */
  KvdbError FoldCreate(const char *fold_path);
  /**
  * @brief �����ļ���
  */
  KvdbError FoldCopy(const char *target_fold, const char *src_fold);
  /**
  * @brief �����ļ�
  */
  KvdbError FileCopy(const char *target_filename, const char *src_filename);
  /**
  * @brief ���ҽڵ�
  */
  struct KvdbRecord *NodeFind(const std::string &key);
  /**
  * @brief ���ҿ��л���ýڵ�
  */
  struct KvdbRecord *NodeOldest(int length);

  char foldpath_[KVDB_FILE_PATH_MAXLEN + 1];
  struct KvdbRecord *cache_list_[KVDB_CACHE_MAXNUM];
  int cache_size_[KVDB_CACHE_MAXNUM];
  int cache_cnt_;
};
}

#endif  // SRC_LIBVZTINYDB_KVDBSERVICE_H_
