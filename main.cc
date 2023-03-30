#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/sdk/version/version.h"
#include "opentelemetry/trace/provider.h"

#include <iostream>

namespace trace_api      = opentelemetry::trace;
namespace trace_sdk      = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;
namespace nostd          = opentelemetry::nostd;
namespace otlp           = opentelemetry::exporter::otlp;

void InitTracer()
{
  opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;
  opts.url = "0.0.0.0:4318";
  auto exporter  = otlp::OtlpHttpExporterFactory::Create(opts);
  auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));
  std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
      trace_sdk::TracerProviderFactory::Create(std::move(processor));

  trace_api::Provider::SetTracerProvider(provider);
}

void CleanupTracer()
{
  std::shared_ptr<opentelemetry::trace::TracerProvider> none;
  trace_api::Provider::SetTracerProvider(none);
}

nostd::shared_ptr<trace_api::Tracer> get_tracer()
{
  auto provider = trace_api::Provider::GetTracerProvider();
  return provider->GetTracer("cpptraceex", OPENTELEMETRY_SDK_VERSION);
}

void f1()
{
  auto scoped_span = trace_api::Scope(get_tracer()->StartSpan("f1"));
  std::cout << "Hello from f1" << std::endl;
}

void f2()
{
  auto scoped_span = trace_api::Scope(get_tracer()->StartSpan("f2"));
  std::cout << "Hello from f2" << std::endl;
  f1();
}

int main(){
  InitTracer();
  f2();
  f1();
  CleanupTracer();
  return 0;
}
