// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CEF_LIBCEF_BROWSER_CONTENT_BROWSER_CLIENT_H_
#define CEF_LIBCEF_BROWSER_CONTENT_BROWSER_CLIENT_H_
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/content_browser_client.h"

class CefBrowserMainParts;
class CefResourceDispatcherHostDelegate;

namespace content {
class SiteInstance;
}

class CefContentBrowserClient : public content::ContentBrowserClient {
 public:
  CefContentBrowserClient();
  virtual ~CefContentBrowserClient();

  void set_browser_main_parts(CefBrowserMainParts* parts) {
    browser_main_parts_ = parts;
  }
  CefBrowserMainParts* browser_main_parts() const {
    return browser_main_parts_;
  }

  virtual content::BrowserMainParts* CreateBrowserMainParts(
      const content::MainFunctionParams& parameters) OVERRIDE;
  virtual content::WebContentsView* CreateWebContentsView(
      content::WebContents* web_contents) OVERRIDE;
  virtual void RenderViewHostCreated(
      RenderViewHost* render_view_host) OVERRIDE;
  virtual void RenderProcessHostCreated(
      content::RenderProcessHost* host) OVERRIDE;
  virtual content::WebUIControllerFactory* GetWebUIControllerFactory() OVERRIDE;
  virtual GURL GetEffectiveURL(content::BrowserContext* browser_context,
                               const GURL& url) OVERRIDE;
  virtual bool ShouldUseProcessPerSite(content::BrowserContext* browser_context,
                                       const GURL& effective_url) OVERRIDE;
  virtual bool IsHandledURL(const GURL& url) OVERRIDE;
  virtual bool IsSuitableHost(content::RenderProcessHost* process_host,
                              const GURL& site_url) OVERRIDE;
  virtual void SiteInstanceGotProcess(
      content::SiteInstance* site_instance) OVERRIDE;
  virtual void SiteInstanceDeleting(
      content::SiteInstance* site_instance) OVERRIDE;
  virtual bool ShouldSwapProcessesForNavigation(const GURL& current_url,
                                                const GURL& new_url) OVERRIDE;

  virtual std::string GetCanonicalEncodingNameByAliasName(
      const std::string& alias_name) OVERRIDE;
  virtual void AppendExtraCommandLineSwitches(CommandLine* command_line,
                                              int child_process_id) OVERRIDE;
  virtual std::string GetApplicationLocale() OVERRIDE;
  virtual std::string GetAcceptLangs(
      content::BrowserContext* context) OVERRIDE;
  virtual SkBitmap* GetDefaultFavicon() OVERRIDE;
  virtual bool AllowAppCache(const GURL& manifest_url,
                             const GURL& first_party,
                             content::ResourceContext* context) OVERRIDE;
  virtual bool AllowGetCookie(const GURL& url,
                              const GURL& first_party,
                              const net::CookieList& cookie_list,
                              content::ResourceContext* context,
                              int render_process_id,
                              int render_view_id) OVERRIDE;
  virtual bool AllowSetCookie(const GURL& url,
                              const GURL& first_party,
                              const std::string& cookie_line,
                              content::ResourceContext* context,
                              int render_process_id,
                              int render_view_id,
                              net::CookieOptions* options) OVERRIDE;
  virtual bool AllowSaveLocalState(
      content::ResourceContext* context) OVERRIDE;
  virtual bool AllowWorkerDatabase(
      const GURL& url,
      const string16& name,
      const string16& display_name,
      unsigned long estimated_size,  // NOLINT(runtime/int)
      content::ResourceContext* context,
      const std::vector<std::pair<int, int> >& render_views) OVERRIDE;
  virtual bool AllowWorkerFileSystem(
      const GURL& url,
      content::ResourceContext* context,
      const std::vector<std::pair<int, int> >& render_views) OVERRIDE;
  virtual net::URLRequestContext* OverrideRequestContextForURL(
      const GURL& url, content::ResourceContext* context) OVERRIDE;
  virtual QuotaPermissionContext* CreateQuotaPermissionContext() OVERRIDE;
  virtual void OpenItem(const FilePath& path) OVERRIDE;
  virtual void ShowItemInFolder(const FilePath& path) OVERRIDE;
  virtual void AllowCertificateError(
      SSLCertErrorHandler* handler,
      bool overridable,
      const base::Callback<void(SSLCertErrorHandler*, bool)>& callback)
      OVERRIDE;
  virtual void SelectClientCertificate(
      int render_process_id,
      int render_view_id,
      SSLClientAuthHandler* handler) OVERRIDE;
  virtual void AddNewCertificate(
      net::URLRequest* request,
      net::X509Certificate* cert,
      int render_process_id,
      int render_view_id) OVERRIDE;
  virtual void RequestDesktopNotificationPermission(
      const GURL& source_origin,
      int callback_context,
      int render_process_id,
      int render_view_id) OVERRIDE;
  virtual WebKit::WebNotificationPresenter::Permission
      CheckDesktopNotificationPermission(
          const GURL& origin,
          content::ResourceContext* context,
          int render_process_id) OVERRIDE;
  virtual void ShowDesktopNotification(
      const content::ShowDesktopNotificationHostMsgParams& params,
      int render_process_id,
      int render_view_id,
      bool worker) OVERRIDE;
  virtual void CancelDesktopNotification(
      int render_process_id,
      int render_view_id,
      int notification_id) OVERRIDE;
  virtual bool CanCreateWindow(
      const GURL& origin,
      WindowContainerType container_type,
      content::ResourceContext* context,
      int render_process_id) OVERRIDE;
  virtual std::string GetWorkerProcessTitle(
      const GURL& url, content::ResourceContext* context) OVERRIDE;
  virtual void ResourceDispatcherHostCreated() OVERRIDE;
  virtual ui::Clipboard* GetClipboard() OVERRIDE;
  virtual MHTMLGenerationManager* GetMHTMLGenerationManager() OVERRIDE;
  virtual net::NetLog* GetNetLog() OVERRIDE;
  virtual speech_input::SpeechInputManager* GetSpeechInputManager() OVERRIDE;
  virtual content::AccessTokenStore* CreateAccessTokenStore() OVERRIDE;
  virtual bool IsFastShutdownPossible() OVERRIDE;
  virtual void OverrideWebkitPrefs(RenderViewHost* rvh,
                                   WebPreferences* prefs) OVERRIDE;
  virtual void UpdateInspectorSetting(RenderViewHost* rvh,
                                      const std::string& key,
                                      const std::string& value) OVERRIDE;
  virtual void ClearInspectorSettings(RenderViewHost* rvh) OVERRIDE;
  virtual void BrowserURLHandlerCreated(BrowserURLHandler* handler) OVERRIDE;
  virtual void ClearCache(RenderViewHost* rvh)  OVERRIDE;
  virtual void ClearCookies(RenderViewHost* rvh)  OVERRIDE;
  virtual FilePath GetDefaultDownloadDirectory() OVERRIDE;
  virtual std::string GetDefaultDownloadName() OVERRIDE;

#if defined(OS_POSIX) && !defined(OS_MACOSX)
  virtual int GetCrashSignalFD(const CommandLine& command_line) OVERRIDE;
#endif

#if defined(OS_WIN)
  virtual const wchar_t* GetResourceDllName() OVERRIDE;
#endif

#if defined(USE_NSS)
  virtual
      crypto::CryptoModuleBlockingPasswordDelegate* GetCryptoPasswordDelegate(
          const GURL& url) OVERRIDE;
#endif

 private:
  CefBrowserMainParts* browser_main_parts_;

  scoped_ptr<CefResourceDispatcherHostDelegate>
      resource_dispatcher_host_delegate_;
};

#endif  // CEF_LIBCEF_BROWSER_CONTENT_BROWSER_CLIENT_H_
